//compares arrays of any size
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

//compares arrays of size three

bool equals(int *arr1, int *arr2) {
	if((arr1[0]==arr2[0])&&(arr1[1]==arr2[1])&&(arr1[2]==arr2[2])){
		return true;
	}
	else{
		return false;
	}
	
bool equals(string str1, string str2){
	StringFind(str1, str2>=0)
} 

//void calculateArrDiff(int *arr1, int *arr2, int size){
//		for
//}
