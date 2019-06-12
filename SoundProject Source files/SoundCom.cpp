//#include "SoundCom.h"
//
//template<class T>
//SoundCom<T>::SoundCom(wstring sOutputDevice,
//  unsigned int nSampleRate, unsigned int nChannels,
//  unsigned int nBlocks, unsigned int nBlockSamples)
//{
//  Create(sOutputDevice, nSampleRate, nChannels, nBlocks, nBlockSamples);
//}
//
//template<class T>
//SoundCom<T>::~SoundCom()
//{
//  Destroy();
//}
//
//template<class T>
//bool SoundCom<T>::Create(wstring sOutputDevice,
//  unsigned int nSampleRate,
//  unsigned int nChannels,
//  unsigned int nBlocks,
//  unsigned int nBlockSamples)
//{
//  m_bReady = false;
//  m_nSampleRate = nSampleRate;
//  m_nChannels = nChannels;
//  m_nBlockCount = nBlocks;
//  m_nBlockSamples = nBlockSamples;
//  m_nBlockFree = m_nBlockCount;
//  m_nBlockCurrent = 0;
//  m_pBlockMemory = nullptr;
//  m_pWaveHeaders = nullptr;
//
//  m_userFunction = nullptr;
//
//  // Validate device
//  vector<wstring> devices = Enumerate();
//  auto d = std::find(devices.begin(), devices.end(), sOutputDevice);
//  if (d != devices.end())
//  {
//    // Device is available
//    int nDeviceID = distance(devices.begin(), d);
//    WAVEFORMATEX waveFormat;
//    waveFormat.wFormatTag = WAVE_FORMAT_PCM;
//    waveFormat.nSamplesPerSec = m_nSampleRate;
//    waveFormat.wBitsPerSample = sizeof(T) * 8;
//    waveFormat.nChannels = m_nChannels;
//    waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
//    waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
//    waveFormat.cbSize = 0;
//
//    // Open Device if valid
//    if (waveOutOpen(&m_hwDevice, nDeviceID, &waveFormat, (DWORD_PTR)waveOutProcWrap, (DWORD_PTR)this, CALLBACK_FUNCTION) != S_OK)
//      return Destroy();
//  }
//
//  // Allocate Wave|Block Memory
//  m_pBlockMemory = new T[m_nBlockCount * m_nBlockSamples];
//  if (m_pBlockMemory == nullptr)
//    return Destroy();
//  ZeroMemory(m_pBlockMemory, sizeof(T) * m_nBlockCount * m_nBlockSamples);
//
//  m_pWaveHeaders = new WAVEHDR[m_nBlockCount];
//  if (m_pWaveHeaders == nullptr)
//    return Destroy();
//  ZeroMemory(m_pWaveHeaders, sizeof(WAVEHDR) * m_nBlockCount);
//
//  // Link headers to block memory
//  for (unsigned int n = 0; n < m_nBlockCount; n++)
//  {
//    m_pWaveHeaders[n].dwBufferLength = m_nBlockSamples * sizeof(T);
//    m_pWaveHeaders[n].lpData = (LPSTR)(m_pBlockMemory + (n * m_nBlockSamples));
//  }
//
//  m_bReady = true;  
//
//  m_thread = thread(&SoundCom::MainThread, this);
//
//  // Start the ball rolling
//  unique_lock<mutex> lm(m_muxBlockNotZero);
//  m_cvBlockNotZero.notify_one();
//
//  return true;
//}
//
//bool SoundCom<class T>::Destroy()
//{
//  return false;
//}
//
//void SoundCom<class T>::Stop()
//{
//  m_bReady = false;
//  m_thread.join();
//}
//
//// Override to process current sample
//double SoundCom<class T>::UserProcess(double dTime)
//{
//  return 0.0;
//}
//
//double SoundCom<class T>::GetTime()
//{
//  return m_dGlobalTime;
//}
//
//vector<wstring> SoundCom<class T>::Enumerate()
//{
//  int nDeviceCount = waveOutGetNumDevs();
//  vector<wstring> sDevices;
//  WAVEOUTCAPS woc;
//  for (int n = 0; n < nDeviceCount; n++)
//    if (waveOutGetDevCaps(n, &woc, sizeof(WAVEOUTCAPS)) == S_OK)
//      sDevices.push_back(woc.szPname);
//  return sDevices;
//}
//
//void SoundCom<class T>::SetUserFunction(double(*func)(double))
//{
//  m_userFunction = func;
//}
//
//double SoundCom<class T>::clip(double dSample, double dMax)
//{
//  if (dSample >= 0.0)
//    return fmin(dSample, dMax);
//  else
//    return fmax(dSample, -dMax);
//}
//
//void SoundCom<class T>::waveOutProc(HWAVEOUT hWaveOut, UINT uMsg, DWORD dwParam1, DWORD dwParam2)
//{
//  if (uMsg != WOM_DONE) return;
//
//  m_nBlockFree++;
//  unique_lock<mutex> lm(m_muxBlockNotZero);
//  m_cvBlockNotZero.notify_one();
//}
//
//// Static wrapper for sound card handler
//void CALLBACK SoundCom<class T>::waveOutProcWrap(HWAVEOUT hWaveOut, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
//{
//  ((SoundCom*)dwInstance)->waveOutProc(hWaveOut, uMsg, dwParam1, dwParam2);
//}
//
//// Main thread. This loop responds to requests from the soundcard to fill 'blocks'
//// with audio data. If no requests are available it goes dormant until the sound
//// card is ready for more data. The block is filled by the "user" in some manner
//// and then issued to the soundcard.
//
//template<class T>
//void SoundCom<T>::MainThread()
//{
//  m_dGlobalTime = 0.0;
//  double dTimeStep = 1.0 / (double)m_nSampleRate;
//
//  // Gets maximum integer for a type at run-time
//  T nMaxSample = (T)pow(2, (sizeof(T) * 8) - 1) - 1;
//  double dMaxSample = (double)nMaxSample;
//  T nPreviousSample = 0;
//
//  while (m_bReady)
//  {
//    // Wait for block to become available
//    if (m_nBlockFree == 0)
//    {
//      unique_lock<mutex> lm(m_muxBlockNotZero);
//      m_cvBlockNotZero.wait(lm);
//    }
//
//    // Block is here, so use it
//    m_nBlockFree--;
//
//    // Prepare block for processing
//    if (m_pWaveHeaders[m_nBlockCurrent].dwFlags & WHDR_PREPARED)
//      waveOutUnprepareHeader(m_hwDevice, &m_pWaveHeaders[m_nBlockCurrent], sizeof(WAVEHDR));
//
//    T nNewSample = 0;
//    int nCurrentBlock = m_nBlockCurrent * m_nBlockSamples;
//
//    for (unsigned int n = 0; n < m_nBlockSamples; n++)
//    {
//      // User Process
//      if (m_userFunction == nullptr)
//        nNewSample = (T)(clip(UserProcess(m_dGlobalTime), 1.0) * dMaxSample);
//      else
//        nNewSample = (T)(clip(m_userFunction(m_dGlobalTime), 1.0) * dMaxSample);
//
//      m_pBlockMemory[nCurrentBlock + n] = nNewSample;
//      nPreviousSample = nNewSample;
//      m_dGlobalTime = m_dGlobalTime + dTimeStep;
//    }
//
//    // Send block to sound device
//    waveOutPrepareHeader(m_hwDevice, &m_pWaveHeaders[m_nBlockCurrent], sizeof(WAVEHDR));
//    waveOutWrite(m_hwDevice, &m_pWaveHeaders[m_nBlockCurrent], sizeof(WAVEHDR));
//    m_nBlockCurrent++;
//    m_nBlockCurrent %= m_nBlockCount;
//  }
//}