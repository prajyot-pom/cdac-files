TARGET=thread2

$(TARGET).out: $(TARGET).o
	gcc -o $(TARGET).out $(TARGET).o -lpthread 

$(TARGET).o: $(TARGET).c
	gcc -c $(TARGET).c

clean:
	rm -f *.o *.out

