package test;

import java.util.ArrayList;

public class Program 
{
	private static ArrayList<Integer> getIntegerList()
	{
		ArrayList<Integer> list = new ArrayList<Integer>();
		list.add(10);
		list.add(20);
		list.add(30);
		return list;
	}
	private static void print(ArrayList<Number> list)
	{
		for( Object element : list )
			System.out.println(element);
	}
	public static void main(String[] args) 
	{	
		ArrayList<Integer> intList = Program.getIntegerList( );
		Program.print( intList ); //Not OK
	}
		
}
