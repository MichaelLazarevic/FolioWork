package senser;

import java.util.ArrayList;

public class AircraftSentenceFactory
{
	public ArrayList<AircraftSentence> fromAircraftJson(String jsonAircraftList)
	{	
		//TODO: Get distinct aircrafts from the jsonAircraftList string		
		// and store them in an ArrayList
		ArrayList<AircraftSentence> listOfSentences = new ArrayList<AircraftSentence>();
		String temp;
		//temp = jsonAircraftList.substring(1, jsonAircraftList.length()-1);
		String[] tempArray = jsonAircraftList.split("(?<=\\}),(?=\\{)");
		for(String temp2 : tempArray)
		{
			listOfSentences.add(new AircraftSentence(temp2));
		}
		return listOfSentences;
	}
}
