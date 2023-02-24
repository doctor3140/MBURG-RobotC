// http://robodesigners.blogspot.com/2012/04/arrays-in-robotc.html

int arr[2][3]= {
		{10, 11, 12},
	  {14, 15, 16}
};

//passing as argument has caused issues
bool test(){
	if(arr[0][0] == 10){
		return true;
	}
		return false;
}

task main(){
	test();
}
