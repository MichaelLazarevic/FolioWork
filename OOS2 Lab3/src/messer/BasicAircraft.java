package messer;

import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.Date;

public class BasicAircraft {
	private String icao;
	private String operator;
	private Integer species;
	private Date posTime;
	private Coordinate coordinate;
	private Double speed;
	private Double trak;
	private Integer altitude;
	
	//TODO: Create constructor
	public BasicAircraft(String tIcao,
			String tOperator,
			Integer tSpecies,
			Date tPosTime,
			Coordinate tCoordinate,
			Double tSpeed,
			Double tTrak,
			Integer tAltitude)
	{
		icao = tIcao;
		operator = tOperator;
		species = tSpecies;
		posTime = tPosTime;
		coordinate = tCoordinate;
		speed = tSpeed;
		trak = tTrak;
		altitude = tAltitude;
	}
	
	//TODO: Create relevant getter methods

	public String getIcao() {
		return icao;
	}

	public void setIcao(String icao) {
		this.icao = icao;
	}

	public String getOperator() {
		return operator;
	}

	public void setOperator(String operator) {
		this.operator = operator;
	}

	public Integer getSpecies() {
		return species;
	}

	public void setSpecies(Integer species) {
		this.species = species;
	}

	public Date getPosTime() {
		return posTime;
	}

	public void setPosTime(Date posTime) {
		this.posTime = posTime;
	}

	public Coordinate getCoordinate() {
		return coordinate;
	}

	public void setCoordinate(Coordinate coordinate) {
		this.coordinate = coordinate;
	}

	public Double getSpeed() {
		return speed;
	}

	public void setSpeed(Double speed) {
		this.speed = speed;
	}

	public Double getTrak() {
		return trak;
	}

	public void setTrak(Double trak) {
		this.trak = trak;
	}

	public Integer getAltitude() {
		return altitude;
	}

	public void setAltitude(Integer altitude) {
		this.altitude = altitude;
	}
	
	//TODO: Lab 4-6 return attribute names and values for table
	public static ArrayList<String> getAttributesNames()
	{
		return null;
	}

	public static ArrayList<Object> getAttributesValues(BasicAircraft ac)
	{
		return null;
	}

	@Override
	public String toString() {
		return "BasicAircraft [icao=" + icao + ", operator=" + operator + ", species=" + species + ", posTime="
				+ posTime + ", coordinates=(" + coordinate.getLatitude() + "," + coordinate.getLongitude() + "), speed=" + speed + ", trak=" + trak + ", altitude="
				+ altitude + "]";
	}

	//TODO: Overwrite toString() method to print fields
	
}
