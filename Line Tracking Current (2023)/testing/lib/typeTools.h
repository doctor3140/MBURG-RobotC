int array1;
int array2;

void setArrays(int *arr1, int *arr2){
	array1 = arr1;
	array2 = arr2;
}


//Array and String Functions
bool equals(int *arr1, int *arr2, int size){
	int equal = 0;
	for(int i = 0; i<size; i++){
		if(arr1[i]==arr2[i]){
			equal++;
		}
	}
	if(equal==size){
		return true;
	}
	else{
		return false;
	}
}
//compares arrays of any size

bool equals(int *arr1, int *arr2) //compares arrays of size three
{
	if((arr1[0]==arr2[0])&&(arr1[1]==arr2[1])&&(arr1[2]==arr2[2])){
		return true;
	}
	else{
		return false;
	}
}
/*
bool inRange(int *arr1, int **arr2) //compares 2d arrays of size three
{
	if((arr1[0][0]==(arr2[0][0]||arr2[0][1]))&&((arr1[1]==(arr2[1][0]||arr2[1][1]))&&(arr1[2]==(arr2[2][0]||arr2[2][1])){
		return true;
	}
	else{
		return false;
	}
}

*/
bool equals(string str1, string str2){
	return (stringFind(str1, str2)>=0);
}

//void calculate(int *arr1, int *arr2, int size){
//		for
//}
