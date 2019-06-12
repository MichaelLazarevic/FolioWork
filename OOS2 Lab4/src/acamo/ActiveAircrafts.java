package acamo;

import java.util.HashMap;
import java.util.Observable;
import java.util.Observer;

import java.util.ArrayList;
import messer.*;

//TODO: create hash map and complete all operations
public class ActiveAircrafts implements Observer
{
	private static boolean lab4 = true;
	private HashMap<String , BasicAircraft> activeAircrafts;    // store the active aircraft 

	public ActiveAircrafts () {
	}

	public synchronized void store(String icao, BasicAircraft ac) {
		activeAircrafts.put(icao,  ac);
	}

	public synchronized void clear() {
		activeAircrafts.clear();
	}

	public synchronized BasicAircraft retrieve(String icao) {
		return activeAircrafts.get(icao);
	}

	public synchronized ArrayList<BasicAircraft> values() {
		ArrayList<BasicAircraft> ListOfAircrafts = new ArrayList<BasicAircraft>();
		for (BasicAircraft ba : activeAircrafts.values())
			ListOfAircrafts.add(ba);
		return ListOfAircrafts;
	}

	public String toString () {
		return activeAircrafts.toString();
	}

	@Override
	// TODO: store arg in hashmap
	public void update(Observable o, Object arg) {
	}
}