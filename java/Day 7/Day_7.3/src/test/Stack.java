package test;

public class Stack
{
	private int top = -1;
	private int[] arr;
	public Stack(  )
	{
		this( 5 );
	}
	public Stack( int size )
	{
		this.arr = new int[ size ];
	}
	public boolean empty( )
	{
		return this.top == -1;
	}
	public boolean full( )
	{
		return this.top == this.arr.length - 1;
	}
	public void push( int element ) throws StackOverflowException
	{
		if( this.full())
			throw new StackOverflowException("Stack is full");
		this.arr[ ++ this.top ] = element;
	}
	public int peek( ) throws StackUnderflowException
	{
		if( this.empty())
			throw new StackUnderflowException("Stack is empty");
		return this.arr[ this.top ];
	}
	public void pop( ) throws StackUnderflowException
	{
		if( this.empty())
			throw new StackUnderflowException("Stack is empty");
		-- this.top;
	}
}
