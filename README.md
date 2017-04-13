# Crypto
A new cryptographic encryption technique

 * This is an asymmetric key encryption technique.
 * In this encryption technique, I have made use of 5 pair of keys.
 * Therefore, we get different encipherment for different plain text.
 * Eg. cipher text of "helloworld" is "DYPPEKQZBF".
 * Here, we can see that 'l' corresponds to 'P' & 'B'. Also 'o' corresponds to 'E' & 'Q'.
 * 5 key-pairs are selected from a set of 12 mod 26 multiplicative inverses.
 * Every new instance will have random keys. Hence, it is more secure.
 * Also, breaking the text will be difficult as we have 5 different keys.
 * These keys are selected at random and in no specific order.
