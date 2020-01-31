public class TehRectangle
{
	private double width = 0;
	private double length = 0;
	private double area = 0;
	private double perimeter = 0;
	
	public TehRectangle(double w, double l)
	{
		width = w;
		length = l;
	}
	public double area()
	{
		area = width*length;
		return area;
	}
	public double perimeter()
	{
		perimeter = (width*2)+(length*2);
		return perimeter;
	}
	public void stats()
	{
		System.out.println("The Length is: "+length);
		System.out.println("The Width is: "+width);
	}
}