import java.util.Scanner;

public class MyPoint
{
	private int x;
	private int y;
	private String pointID;
	
	public MyPoint(String pointID)
	{
		this.x = 0;
		this.y = 0;
		this.pointID = pointID;	
	}
	
	public MyPoint(int x, int y)
	{
		this.x = x;
		this.y = y;
	}
	
	
	public void setX(int x)
	{
		this.x = x;
	}
	
	public void setY(int y)
	{
		this.y = y;
	}
	
	public void setXY(int x, int y)
	{
		this.x = x;
		this.y = y;
	}

	public int getX()
	{
		return x;
	}
	
	public int getY()
	{
		return y;
	}

	public int[] getXY()
	{
		int []arr = new int[2];
		
		arr[0] = x;
		arr[1] = y;
		
		return arr;
	}
	
	public String getID()
	{
		return pointID;
	}
	
	public String toString()
	{
		String l = strProcess(x);
		String r = strProcess(y);
		
		String s = '(' + l + ',' + r + ')';
		
		return s;
	}
	
	public String strProcess(int x)
	{
		String s = "";
		
		while(true)
		{
			int a = x%10;
			x = x/10;
			
			s = (char)(a + '0') + s;
			
			if(x == 0)
			{
				break;
			}
		}
		
		return s;
	}
	
	public double distance(int l , int r)
	{
		return Math.sqrt((l-x)*(l-x) + (r-y)*(r-y));
	}
	
	public double distance(MyPoint A)
	{
		return Math.sqrt((A.getX()-x)*(A.getX()-x) + (A.getY()-y)*(A.getY()-y));
	}
	
	public double distance()
	{
		return Math.sqrt(x*x + y*y);
	}
}
