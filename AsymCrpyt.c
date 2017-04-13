/*
 * Name		:	Alfred Gonsalves
 * Class 	:	B.E. COMPS
 * Roll No	:	6748
 * Topic	:	Asymmetric Key Encryption Technique.
 *
 * DESCRIPTION:
 * This is an asymmetric key encryption technique.
 * In this encryption technique, I have made use of 5 pair of keys.
 * Therefore, we get different encipherment for different plain text.
 * Eg. cipher text of "helloworld" is "DYPPEKQZBF".
 * Here, we can see that 'l' corresponds to 'P' & 'B'. Also 'o' corresponds to 'E' & 'Q'.
 * 5 key-pairs are selected from a set of 12 mod 26 multiplicative inverses.
 * Every new instance will have random keys. Hence, it is more secure.
 * Also, breaking the text will be difficult as we have 5 different keys.
 * These keys are selected at random and in no specific order.
 *
 */
#include<stdio.h>
#include<stdlib.h>

int privateKey[5],publicKey[5];
//set the keys[][] matrix with integers that are modular 26 multiplicative inverses of each other
int keys[12][12] = {{ 1, 1},{ 3, 9},{ 5,21},{ 7,15},{ 9, 3},{11,19},
					{15, 7},{17,23},{19,11},{21, 5},{23,17},{25,25}};
int length;	//length of the plain text and cipher text
char CryptText[100];	//EncrpytedText array is made global

/*
 * The public and private keys are generated from a set of modular 26 multiplicative inverses.
 * 5 keys are selected at random from the set of 12 keys.
 * Hence, at every instance different keys will be generated.
 */
void generateRandomKeys()
{
	int i;
	for(i=0; i<5; i++)	//generate 5 keys
	{
		int r = rand() % 12;	//generate a random integer from 0 to 11
		//store the selected keys into separate arrays
		privateKey[i] = keys[r][0];
		publicKey[i]  = keys[r][1];
	}
}

//Display the 5 key-pairs generated for the particular instance
void displayKeys()
{
	int i;
	printf("\nPrivateKey\tPublicKey\n");
	for(i=0; i<5; i++)
	{
		printf("  %d\t\t  %d\n",privateKey[i],publicKey[i]);
	}
}

//Modular operation
int mod26(int n)
{
	int x;
	x = n % 26;
	if(x < 0)
		x += 26;
	return x;
}

/*
 * To encrypt the text, divide the text into 5 blocks of equal length.
 * We have 5 public keys chosen from the set of public-private key-pairs in a random order.
 * Use each key for the corresponding block of plaintext.
 * Plaintext are considered as small alphabets and Encrypted text as CAPITALS
 * Multiply the plaintext with the publickey and take mod26 and store result in CryptText[]
 */
void encryptText(char PT[], int length, int publicKey[])
{
	int i,j,x;
	int index=0;	//count
	int block_length;
	block_length = length/5;	//plain text is divided into 5 blocks of equal length
	if(length%5 !=0 )
		block_length++;		//extra characters i.e.length cannot be completely divisible by 5

	for(i=0; i<5; i++)
	{
		for(j=0; j<block_length; j++)
		{
			if(index<length)
			{	x = PT[index]-97;
				CryptText[index] = mod26(x * publicKey[i]);
				CryptText[index] = CryptText[index] + 65;
				index++;
			}
			else
				break;
		}
	}
	//Print the encrpted text
	printf("Cipher Text\t => ");
	for(i=0; i<length; i++)
		printf("%c",CryptText[i]);
	printf("\n");
}

/*
 * To decrypt the text, divide the text into 5 blocks of equal length.
 * We have 5 private keys chosen from the set of public-private key-pairs in a random order.
 * Use each key for the corresponding block of encrypted text.
 * Plaintext are considered as small alphabets and Encrypted text as CAPITALS
 * Multiply the encrypted text with the privatekey and take mod26 and store result in Decrypt[]
 */
void decryptText(char CT[], int length, int privateKey[])
{
	int i,j,x;
	int index=0;
	char Decrypt[100];	//Local array to find the decrypted text
	int block_length;
	block_length = length/5;	//encrypted text is divided into 5 blocks of equal length
	if(length%5 !=0 )
		block_length++;		//extra characters i.e.length cannot be completely divisible by 5

	for(i=0; i<5; i++)
	{
		for(j=0; j<block_length; j++)
		{
			if(index<length)
			{
				x = CT[index]-65;
				Decrypt[index] = mod26(x * privateKey[i]);
				Decrypt[index] = Decrypt[index] + 97;
				index++;
			}
			else
				break;
		}
	}
	//Print the decrypted text
	printf("Decrypted Text\t => ");
	for(i=0; i<length; i++)
		printf("%c",Decrypt[i]);
	printf("\n");
}

int main()
{
	int i;
	char PlainText[100];	//Create local PlainText Array to send for encryption

	//Generate 5 random key pairs for encipherment
	generateRandomKeys();
	displayKeys();	//display the keys selected at that instance

//	printf("Enter length of plain text : ");
	scanf("%d",&length);
//	printf("Enter plain text to be encrypted :\n");
	for(i=0; i<length; i++)
		scanf("%c",&PlainText[i]);

	printf("Plain Text\t => ");
	for(i=0; i<length; i++)
		printf("%c",PlainText[i]);
	printf("\n");

	//Use the publicKey of receiver to encrypt PlainText
	encryptText(PlainText, length, publicKey);

	//Use privateKey of receiver to decrypt the encrypted text
	decryptText(CryptText, length, privateKey);
	return 0;
}
/*
***OUTPUT 1
Enter length of plain text : 10
Enter plain text to be encrypted :
helloworld

PrivateKey	PublicKey
  11		  19
  25		  25
  23		  17
  9			  3
  11		  19
Plain Text	 	=> helloworld
Cipher Text	 	=> DYPPEKQZBF
Decrypted Text	=> helloworld

***OUTPUT 2
Enter length of plain text : 17
Enter plain text to be encrypted :
my name is alfred

PrivateKey	PublicKey
  11		  19
  25		  25
  23		  17
  9			  3
  11		  19
Plain Text	 	=> my name is alfred
Cipher Text		=> UONNAOWNGUNAHPZMF
Decrypted Text	=> mynnamenisnalfred
*/
