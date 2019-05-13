CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c
	gcc -o testme -g testme.c $(CFLAGS)


	# gcov dominion.c >> unittestresult.out
	# cat dominion.c.gcov >> unittestresult.out

clean:
	rm -f *.o testme  *.gcov *.gcda *.gcno *.so *.out
