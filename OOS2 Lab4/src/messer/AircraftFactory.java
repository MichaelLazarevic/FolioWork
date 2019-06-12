package messer;

import java.util.Date;
import java.util.regex.*;

import senser.AircraftSentence;

/* Get the following datafields out of the JSON sentence using Regex and String methods
 * and return a BasicAircraft
 * 
 * For Lab3 replace usee JSO parsing instead
 * 
 * "Icao":"3C5467", matches; first part is Icao, second part is 3C5467
 * "Op":"Lufthansa matches; first part is Op, second part is Lufthansa
 * "Species":1, matches; first part is Species, second part is 1
 * "PosTime":1504179914003, matches; first part is PosTime, second part is 1504179914003
 * "Lat":49.1912, matches; first part is Lat, second part is 49.1912
 * "Long":9.3915, matches; first part is Long, second part is 9.3915
 * "Spd":420.7, matches; first part is Spd, second part is 420.7
 * "Trak":6.72, matches; first part is Trak, second part is 6.72
 * "GAlt":34135, matches; first part is GAlt, second part is 34135
 */

public class AircraftFactory {

	public BasicAircraft fromAircraftSentence ( AircraftSentence sentence ) {
		String icao = null;
		String operator = null;
		int species = 0;
		Date posTime = null;
		double longitude = 0;
		double latitude = 0;
		double speed = 0;
		double trak = 0;
		int altitude = 0;

		// TODO: Your code goes here
		String temp = sentence.getSentence();
		
		//WORKS
		icao = findText(temp, "Icao\":\"([a-zA-Z0-9]*)\"");
		
		//KINDA WORK
		operator = findText(temp, "Op\":\"([a-z A-Z]+)\"");
		//operator = findText(temp, "Op\":\"(.+)\"");
		
		//WORKS
		species = Integer.parseInt(findText(temp, "Species\":([0-9]*),"));
		
		//Doesnt work
		posTime = new Date(Long.parseLong(findText(temp, "PosTime\":([0-9]*),")));
		
		//WORK
		longitude = Double.parseDouble(findText(temp, "Long\":([0-9]*\\.?[0-9]*),"));
		
		//WORKS
		latitude = Double.parseDouble(findText(temp, "Lat\":([0-9]*\\.?[0-9]*),"));
		
		//WORKS
		speed = Double.parseDouble(findText(temp, "Spd\":([0-9]*\\.?[0-9]*),"));
		
		//WORKS
		trak = Double.parseDouble(findText(temp, "Trak\":([0-9]*\\.?[0-9]*),"));
		
		//KINDA WORKS
		altitude = Integer.parseInt(findText(temp, "GAlt\":(\\d*)"));

		BasicAircraft msg = new BasicAircraft(icao, operator, species, posTime, new Coordinate(latitude, longitude), speed, trak, altitude);
		
		return msg;
	}
	
	public String findText(String sentence, String textToMatch)
	{
		Pattern expression = Pattern.compile(textToMatch);
		Matcher matcher = expression.matcher(sentence);
		//System.out.println(sentence);
		if(matcher.find())
		{

			return matcher.group(1);
		}
		else
		{
			return "0";
		}
		//System.out.println(matcher.group(1));
	}
}
