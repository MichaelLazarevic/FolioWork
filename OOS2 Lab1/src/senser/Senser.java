package senser;

import java.util.ArrayList;
import java.util.Observable;

import jsonstream.*;

public class Senser extends Observable implements Runnable
{
	private static boolean lab1 = true;
	PlaneDataServer server;

	public Senser(PlaneDataServer server)
	{
		this.server = server;
	}

	private String getSentence()
	{
		String list = server.getPlaneListAsString();
		if (lab1)
		{
			System.out.println(list);
		}
		return list;
	}
	
	public void run()
	{
		ArrayList<AircraftSentence> jsonAircraftList;
		String aircraftList;
		
		//TODO: Create factory and display object 
		AircraftSentenceFactory factory = new AircraftSentenceFactory();
		AircraftSentenceDisplay display = new AircraftSentenceDisplay();
		
		while (true)
		{
			aircraftList = getSentence();
			
			if(aircraftList == null || aircraftList.length() == 0)
				continue;
			
			//TODO: get aircraft list from factory and display place jsons 

			jsonAircraftList = factory.fromAircraftJson(aircraftList);
					
			if (lab1) System.out.println("Current Aircrafts in range " + jsonAircraftList.size());
			
			for(int i = 0; i < jsonAircraftList.size(); i++)
			{
				AircraftSentence sentence = jsonAircraftList.get(i);
				// Display the sentence in Lab 1; disable for other labs
				if (lab1) display.display(sentence);
				System.out.println("Plane Number : " + (i + 1));
				// Notify all observers
				setChanged();
				notifyObservers(sentence);
			}
			if (lab1) System.out.println();
			if (lab1) try {
				Thread.sleep(5000);
			} catch (InterruptedException e) { }
			
		}		
	}
}

