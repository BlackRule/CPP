# CPP
C++ 6 semestr  
```
for(int i = 0; i < n; i++){
    // do something
}
```
## Lab2
### lab2:
Straightforward implementation. I sort/cut/etc. 'students' vector itself...
Also using lambdas here
### lab2_old:
I decided to sort and split a "view" rather than students vector
So there can exist several views (one sorted one way another - some other way or of a different size) for one students vector
But this will result in slowdowns because the memory access is not linear
### lab2_better:
Same as lab2_old but I decided to split student struct into independent variables
There's a view which connects them all

