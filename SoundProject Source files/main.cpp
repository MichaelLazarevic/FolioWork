#include <iostream>

using namespace std;

#include "SoundCom.h"

const unsigned int sampleRate = 22100;
const unsigned int channels = 2;
const unsigned int bufferBlocks = 8;
const unsigned int bBlockSize = 1024;

double leftSinGen(double dTime)
{
  double dOutput = 1.0 * sin(440.0 * 2 * 3.14159 * dTime);
  /*if (dOutput < 0.0)
  {
    dOutput = 0.2;
  }
  else
  {
    dOutput = -0.2;
  }*/
  return dOutput;
}

double rightSinGen(double dTime)
{
  double dOutput = 1.0 * sin(220.0 * 2 * 3.14159 * dTime);
  /*if (dOutput < 0.0)
  {
  dOutput = 0.2;
  }
  else
  {
  dOutput = -0.2;
  }*/
  return dOutput;
}

int main()
{
  // Get all of the sound Hardware
  vector<wstring> devices = SoundCom<short>::Enumerate();

  // Display Found Hardware
  for(auto d : devices) wcout << "Found Output Device: " << d << endl;

  //Create Sound Machine
  SoundCom<short> sound(devices[0], sampleRate, channels, bufferBlocks, bBlockSize);

  //// Link Sin Function to SoundCom
  sound.SetLeftFunction(leftSinGen);
  sound.SetRightFunction(rightSinGen);
  cout << "Press Enter to Continue!" << endl;
  char c;
  cin >> c;
  return 0;
}