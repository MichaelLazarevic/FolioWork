package senser;

public class AircraftSentence
{
	//TODO: Create attributes
	private String aircraft;
	
	//TODO: Create constructor
	public AircraftSentence(String t_Sentence)
	{
		aircraft = t_Sentence;
	}
	//TODO: Create relevant getter methods
	public String getSentence()
	{
		return aircraft;
	}
	
	public void setSentence(String t_Sentence)
	{
		aircraft = t_Sentence;
	}
	
	//TODO: Overwrite toString() method to print sentence
}
