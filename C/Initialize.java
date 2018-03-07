import java.util.Scanner;

public class Initialize
{
	
	public MyPoint[] obj = new MyPoint[10];
	
	public void iterateP()
	{
		for(int i=0; i<10; i++)
		{
			createP(i+1);
		}
	}
	
	public void createP(int i)
	{
		Scanner id = new Scanner(System.in);
		
		String s = "Point100" + (char)(i + '1');
		
		obj[i-1] = new MyPoint(s);
		
		obj[i-1] = new MyPoint(i,i);
		
		/*System.out.println("Do you want to enter your own points? (Enter: 1: yes 2: no)");
		
		int ip = id.nextInt();
			
		if(ip == 1)
		{
			System.out.println("Enter your point x and y serially");
		
			int x = id.nextInt();
			int y = id.nextInt();
		
			obj[i-1] = new MyPoint(x,y);
		
			System.out.println("Do you want to change the points? (Enter 1: yes 2: no)");
		
			int z = id.nextInt();
		
			if(z==1)
			{
				System.out.println("Enter x and y serially");
				x = id.nextInt();
				y = id.nextInt();	
				obj[i-1].setX(x);
				obj[i-1].setY(y);
				//a.setXY(x,y);
			}
		}*/
	}
	
	public void pointCh()
	{
		Scanner id = new Scanner(System.in);
		for(int i=0; i<10; i++)
		{
			System.out.printf("Do you want to check Point100%d?(Enter 1: yes 2: no)\n",i+1);
			int l = id.nextInt();
			id.nextLine();
			if(l == 1)
			{
				System.out.printf("The co-ordinare of x: %d, Co-ordinate of y: %d\n",obj[i].getX(),obj[i].getY());
				int[] arr = obj[i].getXY();
				System.out.printf("(Using getXY)The co-ordinare of x: %d, Co-ordinate of y: %d\n",arr[0],arr[1]);
			}

			System.out.printf("The distance from origin is %f\n",obj[i].distance());
			System.out.printf("Do you want to check distance?(Enter 1: yes 2: no)\n");
			
			int r = id.nextInt();
			id.nextLine();
			if(r == 1)
			{	
				System.out.printf("Which point do you want check distance from?\nEnter full PointId:\n");
				String s = id.nextLine();
				checkDis(obj[i],s);
			}
			System.out.println("Do you want to check distance from a specific distance?(Enter 1: yes 2: no)");
			int m = id.nextInt();
			id.nextLine();
			if(m == 1)
			{	
				System.out.printf("Enter the x & y serially: \n");
				
				int x = id.nextInt();
				int y = id.nextInt();
				
				System.out.printf("The distance from %s is %f\n",obj[i].toString(),obj[i].distance(x,y));
			}
		}
	}
	
	public void checkDis(MyPoint a, String s)
	{
		for(int i=0; i<10; i++)
		{
			if(obj[i].getID().equals(s))
			{
				System.out.printf("The distance from point %s is %f\n",obj[i].getID(),a.distance(obj[i]));
			}
		}
	}
}
