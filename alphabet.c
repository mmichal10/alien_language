#include "alphabet.h"

NODE *newNode();

int main(){
	int L, D, N;
	NODE *dictionary = newNode();
	dictionary->value = -1;
	
	scanf("%d %d %d", &L, &D, &N);
	
	char *word = calloc(L, sizeof(char));

	for(int i = 0; i < D; i++){
		scanf("%s", word);
		add(dictionary, word);
	}
	scanf("\n");
	char signal[1024] = { 0 };
	for(int i = 0; i < N; i++){
		fgets(signal, 1024, stdin);
		signal[strlen(signal) - 1] = 0;
		printf("Case #%d: %d\n", i+1, find(dictionary, signal));
	}

	free(word);
	cleanUp(dictionary);
}

NODE *newNode(){
	NODE *node = calloc(1, sizeof(NODE));
	node->children = 0;
	node->childrenPtr = NULL;
	node->value = NULL;

	return node;
}

int find(NODE *root, char *pattern){
	if(!strlen(pattern)) return 1; 
	
	int capabilities = 0;
	int exprLen = bracketLength(pattern);

	if(exprLen == 1){
		if(root->value == pattern[0] || root->value < 0){
			if(strlen(pattern) == 1)
				return 1;
			for(int i = 0; i < root->children; i++)
				capabilities += find(root->childrenPtr[i], pattern + ((root->value < 0)?0:1)*sizeof(char));			
		}
	}
	else if(exprLen > 1 && root->value > 0){
		for(int i = 1; i < exprLen - 1; i++)
			if(root->value == pattern[i])
			{
				if(exprLen == strlen(pattern) && root->children == 0) return 1;
				for(int j = 0; j < root->children; j++)
					capabilities += find(root->childrenPtr[j], pattern + exprLen*sizeof(char));
			}
	}
	else if(exprLen > 1 && root->value < 0){
		for(int i = 0; i < root->children; i++)
			capabilities += find(root->childrenPtr[i], pattern);
	}

	return capabilities;
}

int add(NODE *root, char *pattern){
	if(root->value == pattern[0] || root->value < 0){
		for(int i = 0; i < root->children; i++)
			if(add(root->childrenPtr[i], pattern + ((root->value < 0)?0:1)*sizeof(char)) > 0) return 1;
		root->children++;
		root->childrenPtr = realloc(root->childrenPtr, root->children*sizeof(NODE*));
		root->childrenPtr[root->children - 1] = newNode();
		add(root->childrenPtr[root->children - 1], pattern + ((root->value < 0)?0:1)*sizeof(char));
		return 1; 
	}

	//nowy wezel 
	if(root->value == NULL && !root->children){
		root->value = pattern[0];
		//jezeli czesc lancucha wciaz nie jest w drzewie
		if(strlen(pattern) > 1){
			root->children++;
			root->childrenPtr = realloc(root->childrenPtr, root->children*sizeof(NODE*));
			root->childrenPtr[root->children - 1] = newNode();
			add(root->childrenPtr[root->children - 1], pattern + sizeof(char));
		}			
		return 1;
	}
	return -1;
}


int bracketLength(char *expression){
	int length = 1;
	if(expression[0] == '(')
		while(expression[length++] != ')');
	
	return length;
}

void cleanUp(NODE *root){
	if(root->children > 0)
		for(int i = 0; i < root->children; i++)
			cleanUp(root->childrenPtr[i]);
	free(root->childrenPtr);
	free(root);
}


