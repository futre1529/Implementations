ALGORITHM :

The premise of polynomial regression is that a data set of n paired (x,y) members:

(1)  (x1,y1), (x2,y2),..... (xn,yn)
can be processed using a least-squares method to create a predictive polynomial equation of degree p: y=f(x)

(2) The essence of the method is to reduce the residual R at each data point:

(3) This is accomplished by first expressing the system in matrix form

(4)  
then solving for the unknown middle column, (e.g. a0,a1,a2 ...) by means of Gauss-Jordan elimination. The resulting values represent the polynomial coefficients for equation y=f(x) above.


Sample Input - Number of cordinate pairs - 6
               Degree of Polynomial - 3

Pairs - (1,4) (2,5) (4,5.5) (8,10) (3.5,7.5) (6,1.5)

Sample Output - a = 1.56653
		b = 4.69817
		c = -1.48372
		d = .127141