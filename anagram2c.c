#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

// trie node
struct TrieNode
{
	struct TrieNode *children[ALPHABET_SIZE];
	bool isEndOfWord;
};

struct TrieNode *createNode(void)
{
	struct TrieNode *pNode = NULL;

	pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));

	if (pNode)
	{
		int i;

		pNode->isEndOfWord = false;

		for (i = 0; i < ALPHABET_SIZE; i++)
			pNode->children[i] = NULL;
	}

	return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, const char *key)
{
	int i;
	int length = strlen(key);
	int index;

	struct TrieNode *pCrawl = root;

	for (i = 0; i < length; i++)
	{
		index = CHAR_TO_INDEX(key[i]);
		if (!pCrawl->children[index])
			pCrawl->children[index] = createNode();

		pCrawl = pCrawl->children[index];
	}


	pCrawl->isEndOfWord = true;
}

bool search(struct TrieNode *root, const char *key)
{
	int i;
	int length = strlen(key);
	int index;
	struct TrieNode *pCrawl = root;

	for (i = 0; i < length; i++)
	{
		index = CHAR_TO_INDEX(key[i]);

		if (!pCrawl->children[index])
			return false;

		pCrawl = pCrawl->children[index];
	}

	return (pCrawl != NULL && pCrawl->isEndOfWord);
}
void setup(struct TrieNode **trie, char filename [])
 {
    FILE *fp = fopen(filename, "r");
    while(!feof(fp)) {
        char word [100];
        fscanf(fp, "%s", word);
        insert(*trie, word);
    }
    fclose(fp);
}
void swap(char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void permute(char *a, int l, int r)
{
   int i;
   if (l == r)
    {


    struct TrieNode *root = createNode();

	 setup(&root,"dataset.txt");

    if(search(root,a))
    {
        printf("%s might be the right word\n",a);
    }
   }
   else
   {
       for (i = l; i <= r; i++)
       {
          swap((a+l), (a+i));
          permute(a, l+1, r);
          swap((a+l), (a+i)); //backtrack
       }
   }
}


void main()
{
    char s[100];
    printf("ENTER THE SHUFFLED TERMS\n");
    printf("-------------------------\n");
    gets(s);
    int length=strlen(s);
    permute(s,0,length-1);
}
