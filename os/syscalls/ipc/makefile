TARGET=signal3

$(TARGET).out: $(TARGET).o
	gcc -o $(TARGET).out $(TARGET).o 

$(TARGET).o: $(TARGET).c
	gcc -c $(TARGET).c

run:
	./$(TARGET).out

clean:
	rm -f *.o *.out

