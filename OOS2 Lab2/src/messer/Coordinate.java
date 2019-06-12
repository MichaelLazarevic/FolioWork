package messer;

public class Coordinate {
	private double latitude;
	private double longitude;
	
	//TODO: Constructor, Getter/Setter and toString()
	public Coordinate(double tLongitude, double tLatitude)
	{
		longitude = tLongitude;
		latitude = tLatitude;
	}
	
	public void setLongitude(double tLongitude)
	{
		longitude = tLongitude;
	}
	
	public void setLatitude(double tLatitude)
	{
		latitude = tLatitude;
	}
	
	public double getLongitude()
	{
		return longitude;
	}
	
	public double getLatitude()
	{
		return latitude;
	}
	
	public String toString()
	{
		return "";
	}
}