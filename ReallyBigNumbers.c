// functions too long
//not best part of code in my life

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int validate(const char * number);
int add(const char* number1, const char* number2, char** result);
int subtract(const char* number1, const char* number2, char** result);
int compare(const char* number1, const char* number2); //Funkcja compare zwraca 0, jeśli liczby reprezentowane przez ciągi znaków number1 i number2 są sobie równe, 1 jeżeli liczba reprezentowana przez ciąg number1 jest większa, -1 jeżeli liczba number2 jest większa, 2 w przypadku błędnych danych wejściowych, 3 kiedy przekazane do funkcji ciągi nie są poprawnymi liczbami całkowitymi.
void read_numb(char* numb, int max);
int multiply(const char* number1, const char* number2, char** result);
int validate_expression(const char *expr);
int calculate(const char* expr, char **result);

int main()
{
	char* tab =(char*) malloc(500), *result;
	if (tab == NULL)
	{
		printf("Failed to allocate memory");
		return 3;
	}
	printf("Put expresion please, example:2973674+4*1566655+15815846456164-999997777774\n: ");
	fgets(tab, 500, stdin);
	strtok(tab, "\n");
	int err = calculate(tab, &result);
	if (err == 2)
	{
		printf("Incorrect input");
		free(tab);
		return 2;

	}
	if (err == 3)
	{

		printf("Failed to allocate memory");
		free(tab);
		return 3;

	}
	printf("%s", result);
	free(result);
	free(tab);
	return 0;
}
void read_numb(char* numb, int max)
{

	int i = 0;
	char ch = 0;
	while (ch != '\n')
	{
		ch = getchar();
		if (ch == '\n')
			break;
		*(numb + i) = ch;
		i++;
		if (i == max)
		{
			while (getchar() != '\n');
			break;
		}
	}
	*(numb + i) = 0;
	return;
}


int validate(const char * number)
{
	if (!number)
		return 2;
	int i = 0;
	int cyfr_test = 0;
	while (*(number + i))
	{
		if (*number == '-' && *(number + 1) == 0)
			return 1;
		if (i == 0)
		{
			if (((*(number) < '0') || (*(number) > '9')) && (*number != '-'))
				return 1;
		}
		else if ((*(number + i) < '0') || (*(number + i) > '9'))
		{
			return 1;
		}
		if ((*(number + i) > '0') && (*(number + i) <= '9'))
			cyfr_test = 1;
		if (*(number + i) == '0' && cyfr_test == 0 && i == 0 && *(number + 1) != 0)
			return 1;

		++i;
	}
	if (i == 0)
		return 1;
	return 0;
}

int validate_expression(const char *expr)
{
	if (expr == NULL)	//72+-7999--5522--9273+-568*3741		posibilities
		return 2;		////////////////////////////////////////	1 = number
	int numb = 2;		////////////////////////////////////////	2 = math operator
	for (int i = 0; *(expr + i); i++)///////////////////////////	3 = number minus
	{									////////////////////////	
		if ( !(*(expr + i) >= '0'&& *(expr + i) <= '9') && (*(expr + i) != '-') && (*(expr + i) != '+') && (*(expr + i) != '*') )
			return 1;
		else if (numb == 2)
		{
			if (*(expr + i) >= '0'&& *(expr + i) <= '9')
			{
				numb = 1;
			}
			else if (*(expr + i) == '-')
			{
				numb = 3;
			}
			else
				return 1;
		}
		else if (numb == 1)
		{
			if (*(expr + i) >= '0'&& *(expr + i) <= '9') 
			{
				numb = 1;
			}
			else if (*(expr + i) == '-' || *(expr + i) == '+' || *(expr + i) == '*')
			{
				numb = 2;
			}
			else 
				return 1;
		}
		else if (numb == 3)
		{
			if (*(expr + i) >= '0'&& *(expr + i) <= '9')
				numb = 1;
			else
				return 1;

		}
	}
	if (numb != 1)
		return 1;
	return 0;
}


int add(const char* number1, const char* number2, char** result)
{
	if ((number1 == NULL) || (number2 == NULL) || (result == NULL))
	{
		return 1;
	}

	if (validate(number2) || validate(number1))
	{
		return 2;
	}

	if (*number1 != '-' && *number2 != '-')
	{

		int i = 0;
		int j = 0;
		int k = 0;

		while (*(number1 + i))
		{
			i++;
		}
		while (*(number2 + j))
		{
			j++;
		}
		int size;

		if (j > i)
			size = j;
		else
			size = i;
		//if (j == i)
		++size;
		*result = (char *)malloc(size + 1);
		if (*result == NULL)
			return 3;

		char* result_p = *result;
		while (k < size)
		{
			*(result_p + k) = '0';
			k++;
		}
		i--; j--;
		if (i >= j)
		{
			for (k = 0; i >= 0; --i, --j, ++k)
			{
				if (j >= 0)
					*(result_p + k) += *(number1 + i) + *(number2 + j) - (2 * 48);
				else
					*(result_p + k) += *(number1 + i) - 48;
				if ((*(result_p + k) - 48) > 9)
				{
					*(result_p + k) -= 10;
					if (k + 1 >= size)  /* - 1 wywalone z wersji ze stat, alok. bo terminator uwzgledniony w mallocu */
						return 0;
					*(result_p + k + 1) += 1;
					if (i == 0) ++k;
				}
			}
			*(result_p + k) = 0;
		}
		else
		{
			for (k = 0; j >= 0; --j, --i, ++k)
			{
				if (i >= 0)
					*(result_p + k) += *(number1 + i) + *(number2 + j) - (2 * 48);
				else
					*(result_p + k) += *(number2 + j) - 48;
				if ((*(result_p + k) - 48) > 9)
				{
					*(result_p + k) -= 10;
					if (k + 1 >= size)  /* - 1 wywalone z wersji ze stat, alok. bo terminator uwzgledniony w mallocu */
						return 0;
					*(result_p + k + 1) += 1;
					if (j == 0) ++k;
				}
			}
			*(result_p + k) = 0;
		}
		k--;

		for (i = 0; i < k; ++i, --k)
		{
			j = *(result_p + i);
			*(result_p + i) = *(result_p + k);
			*(result_p + k) = j;
		}

		return 0;

	}
	else if (*number1 == '-' && *number2 == '-')
	{

		int i = 0;
		int j = 0;
		int k = 0;

		while (*(number1 + i))
		{
			i++;
		}
		while (*(number2 + j))
		{
			j++;
		}
		int size;
		if (j > i)
			size = j;
		else
			size = i;
		//if (j == i)
		++size;

		*result = (char *)malloc(size + 1); // +1 na terminator
		if (*result == NULL)
			return 3;

		char* result_p = *result;
		while (k < size)
		{
			*(result_p + k) = '0';
			k++;
		}
		i--; j--;
		if (i >= j)
		{
			for (k = 0; i >= 1; --i, --j, ++k)
			{
				if (j >= 1)
					*(result_p + k) += *(number1 + i) + *(number2 + j) - (2 * 48);
				else
					*(result_p + k) += *(number1 + i) - 48;
				if ((*(result_p + k) - 48) > 9)
				{
					*(result_p + k) -= 10;
					if (k + 1 >= size)  /* - 1 wywalone z wersji ze stat, alok. bo terminator uwzgledniony w mallocu */
						return 0;
					*(result_p + k + 1) += 1;
					if (i == 0) ++k;
				}
			}
		}
		else
		{
			for (k = 0; j >= 1; --j, --i, ++k)
			{
				if (i >= 1)
					*(result_p + k) += *(number1 + i) + *(number2 + j) - (2 * 48);
				else
					*(result_p + k) += *(number2 + j) - 48;
				if ((*(result_p + k) - 48) > 9)
				{
					*(result_p + k) -= 10;
					if (k + 1 >= size)  /* - 1 wywalone z wersji ze stat, alok. bo terminator uwzgledniony w mallocu */
						return 0;
					*(result_p + k + 1) += 1;
					if (j == 0) ++k;
				}
			}
		}

		while (*(result_p + k) == '0') {
			*(result_p + k) = 0;
			k--;
		}
		++k;
		*(result_p + k) = '-';
		++k;
		*(result_p + k) = 0;
		--k;
		for (i = 0; i < k; ++i, --k)
		{
			j = *(result_p + i);
			*(result_p + i) = *(result_p + k);
			*(result_p + k) = j;
		}

		return 0;

	}
	else if (*number1 == '-' && *number2 != '-')
	{
		int val = compare((number1 + 1), number2);

		if (val == 0)   //zerowanie
		{
			*result = (char *)malloc(2);
			if (*result == NULL) return 3;
			**(result) = '0';
			*(*result + 1) = 0;
			return 0;
		}
		else if (val == 1)  //wart bezwzgl ujemnnej wieksza :) odejmuje od ujemnej dodatnia i dodaje minus na poczatek
		{
			int i = 0;
			int j = 0;
			int k = 0;

			while (*(number1 + i))
			{
				i++;
			}
			while (*(number2 + j))
			{
				j++;
			}
			int size;
			/*if (j > i)
			size = j;
			else*/
			size = i;   // i zawsze bedzie wieksze bo np -9 vs 8 maks bo  n1 + 1 wieksze

			*result = (char *)malloc(size + 1);
			if (*result == NULL)
				return 3;
			char* result_p = *result;

			while (k < size)
			{
				*(result_p + k) = '0';
				k++;
			}
			i--; j--;
			if (i >= j)
			{
				for (k = 0; i >= 1; --i, --j, ++k)
				{
					if (j >= 0)
						*(result_p + k) += *(number1 + i) - *(number2 + j);     // zmieniony znak i '+ 48'
					else
						*(result_p + k) += *(number1 + i) - 48;
					if ((*(result_p + k) - 48) < 0) // wait
					{
						*(result_p + k) += 10;
						if (k + 1 >= size)  /* -1 wywalone z wersji ze stat, alok. bo terminator uwzgledniony w mallocu */
							return 0;
						*(result_p + k + 1) -= 1;
						if (i == 0) ++k;
					}
				}   //wait 
			}
			else
			{
				for (k = 0; j >= 0; --j, --i, ++k)
				{
					if (i >= 0)
						*(result_p + k) += *(number1 + i) + *(number2 + j) - (2 * 48);
					else
						*(result_p + k) += *(number2 + j) - 48;
					if ((*(result_p + k) - 48) < 0)
					{
						*(result_p + k) += 10;
						if (k + 1 >= size)  /* - 1 wywalone z wersji ze stat, alok. bo terminator uwzgledniony w mallocu */
							return 0;
						*(result_p + k + 1) -= 1;
						if (j == 0) ++k;
					}
				}

			}

			while (*(result_p + k) == '0') {
				*(result_p + k) = 0;
				k--;
			}
			++k;
			*(result_p + k) = '-';
			++k;
			*(result_p + k) = 0;
			--k;
			for (i = 0; i < k; ++i, --k)
			{
				j = *(result_p + i);
				*(result_p + i) = *(result_p + k);
				*(result_p + k) = j;
			}

			return 0;


		}
		else if (val == -1)  //wart ujemnej mniejsza odejmuje od drugiej pierwsza    -9999999999     10000000000
		{
			int i = 0;
			int j = 0;
			int k = 0;

			while (*(number1 + i))
			{
				i++;
			}
			while (*(number2 + j))
			{
				j++;
			}
			int size;
			if (j > i)
				size = j;
			else
				size = i;

			*result = (char *)malloc(size + 1);
			if (*result == NULL)
				return 3;
			char* result_p = *result;

			while (k < size)
			{
				*(result_p + k) = '0';
				k++;
			}
			i--; j--;
			if (i >= j)
			{
				for (k = 0; i >= 1; --i, --j, ++k)
				{
					if (i >= 1)
						*(result_p + k) += *(number2 + j) - *(number1 + i);     // zmieniony znak i '+ 48'
					else
						*(result_p + k) += *(number2 + j) - 48;
					if ((*(result_p + k) - 48) < 0) // wait
					{
						*(result_p + k) += 10;
						if (k + 1 >= size)  /* -1 wywalone z wersji ze stat, alok. bo terminator uwzgledniony w mallocu */
							return 0;
						*(result_p + k + 1) -= 1;
						if (i == 0) ++k;
					}
				}   //wait 

				*(result_p + k) = 0;
			}
			else
			{
				for (k = 0; j >= 0; --j, --i, ++k)
				{
					if (i >= 1)
						*(result_p + k) += *(number2 + j) - *(number1 + i);
					else
						*(result_p + k) += *(number2 + j) - 48;
					if ((*(result_p + k) - 48) < 0)
					{
						*(result_p + k) += 10;
						if (k + 1 >= size)  /* - 1 wywalone z wersji ze stat, alok. bo terminator uwzgledniony w mallocu */
							return 0;
						*(result_p + k + 1) -= 1;
						if (j == 0) ++k;
					}
				}
				*(result_p + k) = 0;
			}
			k--;

			while (*(result_p + k) == '0') {
				*(result_p + k) = 0;
				k--;

			}

			for (i = 0; i < k; ++i, --k)
			{
				j = *(result_p + i);
				*(result_p + i) = *(result_p + k);
				*(result_p + k) = j;
			}

			return 0;

		}
		else
			return 2;


	}
	else if (*number1 != '-' && *number2 == '-')// pierwsza dodatnia druga ujemna
	{
		int val = compare(number1, number2 + 1);

		if (val == 0)   //zerowanie
		{
			*result = (char *)malloc(2);
			if (*result == NULL) return 3;
			**(result) = '0';
			*(*result + 1) = 0;
			return 0;
		}
		else if (val == 1)  // wart. bezwzgl. dodatniej wieksza -> od dodatniej odjąc ujemna
		{
			int i = 0;
			int j = 0;
			int k = 0;

			while (*(number1 + i))
			{
				i++;
			}
			while (*(number2 + j))
			{
				j++;
			}
			int size;
			if (j > i)
				size = j;
			else
				size = i;   // i zawsze bedzie wieksze bo np -9 vs 8 maks bo  n1 + 1 wieksze

			*result = (char *)malloc(size + 1);
			if (*result == NULL)
				return 3;
			char* result_p = *result;

			while (k < size)
			{
				*(result_p + k) = '0';
				k++;
			}
			i--; j--;
			if (i >= j)
			{
				for (k = 0; i >= 0; --i, --j, ++k)
				{
					if (j >= 1)
						*(result_p + k) += *(number1 + i) - *(number2 + j);     // zmieniony znak i '+ 48'
					else
						*(result_p + k) += *(number1 + i) - 48;
					if ((*(result_p + k) - 48) < 0) // wait
					{
						*(result_p + k) += 10;
						if (k + 1 >= size)  /* -1 wywalone z wersji ze stat, alok. bo terminator uwzgledniony w mallocu */
							return 0;
						*(result_p + k + 1) -= 1;
						if (i == 0) ++k;
					}
				}   //wait 
			}
			else
			{
				for (k = 0; j >= 1; --j, --i, ++k)
				{
					if (i >= 0)
						*(result_p + k) += *(number1 + i) - *(number2 + j);
					else
						*(result_p + k) += *(number2 + j) - 48;
					if ((*(result_p + k) - 48) < 0)
					{
						*(result_p + k) += 10;
						if (k + 1 >= size)  /* - 1 wywalone z wersji ze stat, alok. bo terminator uwzgledniony w mallocu */
							return 0;
						*(result_p + k + 1) -= 1;
						if (j == 0) ++k;
					}
				}

			}
			--k;
			while (*(result_p + k) == '0') {
				*(result_p + k) = 0;
				k--;
			}
			++k;
			//*(result_p + k) = '-';
			//++k;
			*(result_p + k) = 0;
			--k;
			for (i = 0; i < k; ++i, --k)
			{
				j = *(result_p + i);
				*(result_p + i) = *(result_p + k);
				*(result_p + k) = j;
			}

			return 0;
		}
		else if (val == -1) //wart ujemnej wieksza odejmuje od drugiej pierwsza i minus na poczatek
		{
			int i = 0;
			int j = 0;
			int k = 0;

			while (*(number1 + i))
			{
				i++;
			}
			while (*(number2 + j))
			{
				j++;
			}
			int size;
			if (j > i)
				size = j;
			else
				size = i;

			*result = (char *)malloc(size + 1);
			if (*result == NULL)
				return 3;
			char* result_p = *result;

			while (k < size)
			{
				*(result_p + k) = '0';
				k++;
			}
			i--; j--;
			if (i >= j)
			{
				for (k = 0; i >= 0; --i, --j, ++k)
				{
					if (j >= 1)
						*(result_p + k) += *(number2 + j) - *(number1 + i);     // zmieniony znak i '+ 48'
					else
						*(result_p + k) += *(number2 + j) - 48;
					if ((*(result_p + k) - 48) < 0) // wait
					{
						*(result_p + k) += 10;
						if (k + 1 >= size)  /* -1 wywalone z wersji ze stat, alok. bo terminator uwzgledniony w mallocu */
							return 0;
						*(result_p + k + 1) -= 1;
						if (i == 0) ++k;
					}
				}   //wait 


			}
			else
			{
				for (k = 0; j >= 1; --j, --i, ++k)
				{
					if (i >= 0)
						*(result_p + k) += *(number2 + j) - *(number1 + i);
					else
						*(result_p + k) += *(number2 + j) - 48;
					if ((*(result_p + k) - 48) < 0)
					{
						*(result_p + k) += 10;
						if (k + 1 >= size)  /* - 1 wywalone z wersji ze stat, alok. bo terminator uwzgledniony w mallocu */
							return 0;
						*(result_p + k + 1) -= 1;
						if (j == 0) ++k;
					}
				}

			}
			while (*(result_p + k) == '0') {
				*(result_p + k) = 0;
				k--;

			}
			k++;
			*(result_p + k) = '-';
			k++;
			*(result_p + k) = 0;


			k--;



			for (i = 0; i < k; ++i, --k)
			{
				j = *(result_p + i);
				*(result_p + i) = *(result_p + k);
				*(result_p + k) = j;
			}

			return 0;
		}
		else
			return 2;
	}
	else
		return 2;

}

int subtract(const char* number1, const char* number2, char** result)
{
	if ((number1 == NULL) || (number2 == NULL) || (result == NULL))
	{
		return 1;
	}

	if (validate(number2) || validate(number1))
	{
		return 2;
	}

	if (*number1 != '-' && *number2 != '-')
	{
		int val = compare(number1, number2);

		if (val == 0)   //zerowanie
		{
			*result = (char *)malloc(2);
			if (*result == NULL) return 3;
			*(*result) = '0';
			*(*result + 1) = 0;
			return 0;
		}
		if (val == 1)
		{
			int i = 0;
			int j = 0;
			int k = 0;

			while (*(number1 + i))
			{
				i++;
			}
			while (*(number2 + j))
			{
				j++;
			}
			int size;
			if (j > i)
				size = j;
			else
				size = i;

			*result = (char *)malloc(size + 1);
			if (*result == NULL) return 3;
			char* result_p = *result;

			while (k < size)
			{
				*(result_p + k) = '0';
				k++;
			}
			i--; j--;
			if (i >= j)
			{
				for (k = 0; i >= 0; --i, --j, ++k)
				{
					if (j >= 0)
						*(result_p + k) += *(number1 + i) - *(number2 + j);     // zmieniony znak i '+ 48'
					else
						*(result_p + k) += *(number1 + i) - 48;
					if ((*(result_p + k) - 48) < 0) // wait
					{
						*(result_p + k) += 10;
						if (k + 1 >= size)  /* -1 wywalone z wersji ze stat, alok. bo terminator uwzgledniony w mallocu */
							return 0;
						*(result_p + k + 1) -= 1;
						if (i == 0) ++k;
					}
				}   //wait 

			}
			else
			{
				for (k = 0; j >= 0; --j, --i, ++k)
				{
					if (i >= 0)
						*(result_p + k) += *(number1 + i) - *(number2 + j);
					else
						*(result_p + k) += *(number2 + j) - 48;
					if ((*(result_p + k) - 48) < 9)
					{
						*(result_p + k) -= 10;
						if (k + 1 >= size)  /* - 1 wywalone z wersji ze stat, alok. bo terminator uwzgledniony w mallocu */
							return 0;
						*(result_p + k + 1) += 1;
						if (j == 0) ++k;
					}
				}
			}
			k--;
			while (*(result_p + k) == '0') {
				*(result_p + k) = 0;
				k--;
			}
			++k;
			*(result_p + k) = 0;
			--k;
			for (i = 0; i < k; ++i, --k)
			{
				j = *(result_p + i);
				*(result_p + i) = *(result_p + k);
				*(result_p + k) = j;
			}

			return 0;
		}
		else if (val == -1)
		{
			int i = 0;
			int j = 0;
			int k = 0;

			while (*(number1 + i))
			{
				i++;
			}
			while (*(number2 + j))
			{
				j++;
			}
			int size;
			if (j > i)
				size = j;
			else
				size = i;
			size++;
			*result = (char *)malloc(size + 1);
			if (*result == NULL) return 3;
			char* result_p = *result;

			while (k < size)
			{
				*(result_p + k) = '0';
				k++;
			}
			i--; j--;
			if (i >= j)
			{
				for (k = 0; i >= 0; --i, --j, ++k)
				{
					if (j >= 0)
						*(result_p + k) += *(number2 + j) - *(number1 + i);     // zmieniony znak i '+ 48'
					else
						*(result_p + k) += *(number2 + j) - 48;
					if ((*(result_p + k) - 48) < 0) // wait
					{
						*(result_p + k) += 10;
						if (k + 1 >= size)  /* -1 wywalone z wersji ze stat, alok. bo terminator uwzgledniony w mallocu */
							return 0;
						*(result_p + k + 1) -= 1;
						if (i == 0) ++k;
					}
				}   //wait 
			}
			else
			{
				for (k = 0; j >= 0; --j, --i, ++k)
				{
					if (i >= 0)
						*(result_p + k) += *(number2 + j) - *(number1 + i);
					else
						*(result_p + k) += *(number2 + j) - 48;
					if ((*(result_p + k) - 48) < 0)
					{
						*(result_p + k) += 10;
						if (k + 1 >= size)  /* - 1 wywalone z wersji ze stat, alok. bo terminator uwzgledniony w mallocu */
							return 0;
						*(result_p + k + 1) -= 1;
						if (j == 0) ++k;
					}
				}
			}

			k--;    //443 489
			while (*(result_p + k) == '0') {
				*(result_p + k) = 0;
				k--;
			}
			++k;

			*(result_p + k) = '-';
			k++;
			*(result_p + k) = 0;
			k--;

			for (i = 0; i < k; ++i, --k)
			{
				j = *(result_p + i);
				*(result_p + i) = *(result_p + k);
				*(result_p + k) = j;
			}

			return 0;

		}
		else
			return 2;
	}
	else if (*number1 == '-' && *number2 == '-')    // dwa minusy = plus
	{
		int val = compare(number1 + 1, number2 + 1);

		if (val == 0)   //zerowanie
		{
			*result = (char *)malloc(2);
			if (*result == NULL) return 3;
			**(result) = '0';
			*(*result + 1) = 0;
			return 0;
		}
		else if (val == 1)  //wart bezwzgl pierwszej(ujemnej) wieksza odejmin od pierwszej druga i zostaw minus na koncu
		{
			int i = 0;
			int j = 0;
			int k = 0;

			while (*(number1 + i))
			{
				i++;
			}
			while (*(number2 + j))
			{
				j++;
			}
			int size;
			if (j > i)
				size = j;
			else
				size = i;   // i zawsze bedzie wieksze bo np -9 vs 8 maks bo  n1 + 1 wieksze

			*result = (char *)malloc(size + 1);
			if (*result == NULL)
				return 3;
			char* result_p = *result;

			while (k < size)
			{
				*(result_p + k) = '0';
				k++;
			}
			i--; j--;
			if (i >= j)
			{
				for (k = 0; i >= 1; --i, --j, ++k)
				{
					if (j >= 1)
						*(result_p + k) += *(number1 + i) - *(number2 + j);     // zmieniony znak i '+ 48'
					else
						*(result_p + k) += *(number1 + i) - 48;
					if ((*(result_p + k) - 48) < 0) // wait
					{
						*(result_p + k) += 10;
						if (k + 1 >= size)  /* -1 wywalone z wersji ze stat, alok. bo terminator uwzgledniony w mallocu */
							return 0;
						*(result_p + k + 1) -= 1;
						//if (i == 0) ++k;
					}
				}   //wait 
			}
			else
			{
				for (k = 0; j >= 1; --j, --i, ++k)
				{
					if (i >= 1)
						*(result_p + k) += *(number1 + i) + *(number2 + j) - (2 * 48);
					else
						*(result_p + k) += *(number2 + j) - 48;
					if ((*(result_p + k) - 48) > 9)
					{
						*(result_p + k) -= 10;
						if (k + 1 >= size)  /* - 1 wywalone z wersji ze stat, alok. bo terminator uwzgledniony w mallocu */
							return 0;
						*(result_p + k + 1) += 1;
						//if (j == 0) ++k;
					}
				}

			}

			while (*(result_p + k) == '0') {
				*(result_p + k) = 0;
				k--;
			}
			++k;
			*(result_p + k) = '-';
			++k;
			*(result_p + k) = 0;
			--k;
			for (i = 0; i < k; ++i, --k)
			{
				j = *(result_p + i);
				*(result_p + i) = *(result_p + k);
				*(result_p + k) = j;
			}

			return 0;


		}
		else if (val == -1) //wart ujemnej mniejsza odejmuje od drugiej pierwsza
		{
			int i = 0;
			int j = 0;
			int k = 0;

			while (*(number1 + i))
			{
				i++;
			}
			while (*(number2 + j))
			{
				j++;
			}
			int size;
			if (j > i)
				size = j;
			else
				size = i;

			*result = (char *)malloc(size + 1);
			if (*result == NULL)
				return 3;
			char* result_p = *result;

			while (k < size)
			{
				*(result_p + k) = '0';
				k++;
			}
			i--; j--;
			if (i >= j)
			{
				for (k = 0; i >= 1; --i, --j, ++k)
				{
					if (i >= 1)
						*(result_p + k) += *(number2 + j) - *(number1 + i);     // zmieniony znak i '+ 48'
					else
						*(result_p + k) += *(number2 + j) - 48;
					if ((*(result_p + k) - 48) < 0) // wait
					{
						*(result_p + k) += 10;
						if (k + 1 >= size)  /* -1 wywalone z wersji ze stat, alok. bo terminator uwzgledniony w mallocu */
							return 0;
						*(result_p + k + 1) -= 1;
						if (i == 0) ++k;
					}
				}   //wait 

				*(result_p + k) = 0;
			}
			else
			{
				for (k = 0; j >= 1; --j, --i, ++k)
				{
					if (i >= 1)
						*(result_p + k) += *(number2 + j) - *(number1 + i);
					else
						*(result_p + k) += *(number2 + j) - 48;
					if ((*(result_p + k) - 48) < 0)
					{
						*(result_p + k) += 10;
						if (k + 1 >= size)  /* - 1 wywalone z wersji ze stat, alok. bo terminator uwzgledniony w mallocu */
							return 0;
						*(result_p + k + 1) -= 1;
						if (j == 0) ++k;
					}
				}
				*(result_p + k) = 0;
			}
			k--;

			while (*(result_p + k) == '0') {
				*(result_p + k) = 0;
				k--;

			}

			for (i = 0; i < k; ++i, --k)
			{
				j = *(result_p + i);
				*(result_p + i) = *(result_p + k);
				*(result_p + k) = j;
			}

			return 0;

		}
		else
			return 2;


	}
	else if (*number1 == '-' && *number2 != '-') //     -9999999999     10000000000
	{
		int i = 0;
		int j = 0;
		int k = 0;

		while (*(number1 + i))
		{
			i++;
		}
		while (*(number2 + j))
		{
			j++;
		}
		int size;
		if (j > i)
			size = j;
		else
			size = i;
		//if (j == i)
		size += 2;
		*result = (char *)malloc(size + 1); // +1 na terminator
		if (*result == NULL)
			return 3;

		char* result_p = *result;
		while (k < size)
		{
			*(result_p + k) = '0';
			k++;
		}
		i--; j--;
		if (i >= j)
		{
			for (k = 0; i >= 0; --i, --j, ++k)
			{
				if (j >= 0)
					*(result_p + k) += *(number2 + j) - 48;
				if (i >= 1)
					*(result_p + k) += *(number1 + i) - 48;
				if ((*(result_p + k) - 48) > 9)
				{
					*(result_p + k) -= 10;
					if (k + 1 >= size)  /* - 1 wywalone z wersji ze stat, alok. bo terminator uwzgledniony w mallocu */
						return 0;
					*(result_p + k + 1) += 1;
					if (i == 0) ++k;
				}
			}
		}
		else
		{
			for (k = 0; j >= 0; --j, --i, ++k)
			{
				if (i >= 1)
					*(result_p + k) += *(number1 + i) + *(number2 + j) - (2 * 48);
				else
					*(result_p + k) += *(number2 + j) - 48;
				if ((*(result_p + k) - 48) > 9)
				{
					*(result_p + k) -= 10;
					if (k + 1 >= size)  /* - 1 wywalone z wersji ze stat, alok. bo terminator uwzgledniony w mallocu */
						return 0;
					*(result_p + k + 1) += 1;
					if (j == 0) ++k;
				}
			}
		}

		while (*(result_p + k) == '0') {
			*(result_p + k) = 0;
			k--;
		}
		++k;
		*(result_p + k) = '-';
		++k;
		*(result_p + k) = 0;
		--k;
		for (i = 0; i < k; ++i, --k)
		{
			j = *(result_p + i);
			*(result_p + i) = *(result_p + k);
			*(result_p + k) = j;
		}

		return 0;


	}
	else if (*number1 != '-' && *number2 == '-')
	{

		int i = 0;
		int j = 0;
		int k = 0;

		while (*(number1 + i))
		{
			i++;
		}
		while (*(number2 + j))
		{
			j++;
		}
		int size;
		if (j > i)
			size = j;
		else
			size = i;
		//if (j == i)
		++size;
		*result = (char *)malloc(size + 1);
		if (*result == NULL)
			return 3;

		char* result_p = *result;
		while (k < size)
		{
			*(result_p + k) = '0';
			k++;
		}
		i--; j--;
		if (i >= j)
		{
			for (k = 0; i >= 0; --i, --j, ++k)
			{
				if (j >= 1)
					*(result_p + k) += *(number2 + j) - 48;

				if (i >= 0)
					*(result_p + k) += *(number1 + i) - 48;

				if ((*(result_p + k) - 48) > 9)
				{
					*(result_p + k) -= 10;
					if (k + 1 >= size)  /* - 1 wywalone z wersji ze stat, alok. bo terminator uwzgledniony w mallocu */
						return 0;
					*(result_p + k + 1) += 1;
					if (i == 0) ++k;
				}
			}
			*(result_p + k) = 0;
		}
		else
		{
			for (k = 0; j >= 1; --j, --i, ++k)
			{
				if (j >= 1)
					*(result_p + k) += *(number2 + j) - 48;

				if (i >= 0)
					*(result_p + k) += *(number1 + i) - 48;

				if ((*(result_p + k) - 48) > 9)
				{
					*(result_p + k) -= 10;
					if (k + 1 >= size)  /* - 1 wywalone z wersji ze stat, alok. bo terminator uwzgledniony w mallocu */
						return 0;
					*(result_p + k + 1) += 1;
					if (j == 1) ++k;
				}
			}
			*(result_p + k) = 0;
		}
		k--;

		for (i = 0; i < k; ++i, --k)
		{
			j = *(result_p + i);
			*(result_p + i) = *(result_p + k);
			*(result_p + k) = j;
		}

		return 0;

	}
	else
		return 2;
	return 2;
}

int compare(const char* number1, const char* number2)
{
	if (!number1 || !number2)
		return 2;
	if (validate(number1) || validate(number2))
		return 3;
	if (*number1 != '-' && *number2 != '-')
	{
		int i, j;

		for (i = 0; *(number1 + i); ++i) {}
		for (j = 0; *(number2 + j); ++j) {}
		if (i > j) return 1;
		if (i < j) return-1;

		for (i = 0; *(number1 + i) && *(number2 + i); ++i)
		{
			if (*(number1 + i) > *(number2 + i))
				return 1;// n1 wieksza
			if (*(number1 + i) < *(number2 + i))
				return -1;// n2 wieksza
		}
		if (*(number1 + i) == 0 && *(number2 + i) == 0)
			return 0;
		if (*(number1 + i) != 0 && *(number2 + i) == 0)
			return 1;
		if (*(number1 + i) == 0 && *(number2 + i) != 0)
			return -1;
	}
	else if (*number1 == '-' && *number2 == '-')
	{
		int i, j;
		for (i = 1; *(number1 + i); ++i) {}
		for (j = 1; *(number2 + j); ++j) {}
		if (i > j) return -1;
		if (j < i) return 1;

		for (i = 1; *(number1 + i) && *(number2 + i); ++i)
		{
			if (*(number1 + i) < *(number2 + i))
				return 1;// n2 wieksza
			if (*(number1 + i) > *(number2 + i))
				return -1;// n1 wieksza
		}
		if (*(number1 + i) == 0 && *(number2 + i) == 0)
			return 0;
		if (*(number1 + i) != 0 && *(number2 + i) == 0)
			return -1;
		if (*(number1 + i) == 0 && *(number2 + i) != 0)
			return 1;

	}
	else if (*number1 == '-' && *number2 != '-')
	{
		return -1; // n2 dodatnia i wieksza n1 ujemna
	}
	else if (*number1 != '-' && *number2 == '-')
	{
		return 1;// n1 dodatnia i wieksza n2 ujemna
	}


	return 1;
}

int multiply(const char* number1, const char* number2, char** result)
{
	if ((number1 == NULL) || (number2 == NULL) || (result == NULL))
	{
		return 1;
	}

	if (validate(number2) || validate(number1))
	{
		return 2;
	}

	if (*number1=='0' || *number2 == '0')   //zerowanie
	{
		*result = (char *)malloc(2);
		if (*result == NULL) return 3;
		*(*result) = '0';
		*(*result + 1) = 0;
		return 0;
	}


	if (*number1 != '-' && *number2 != '-')
	{
			int i = 0;
			int j = 0;
			int k = 0;
			while (*(number1 + i))
			{
				i++;
			}
			while (*(number2 + j))
			{
				j++;
			}
			int size;	// wielkosc pamieci
			int multipler;
			size = strlen(number1) + strlen(number2);
			size += 2;
			*result = (char *)malloc(size);
			
			if (*result == NULL)
				return 3;
			char* result_p = *result;
			k = 0;
			while (k < size)
			{
				*(result_p + k) = 0;
				k++;
			}
			i--; j--;
			int lic;
			int n1_len = i; int n2_len = j;
			if (i >= j)		// number1 longer bigger or same lng
			{
				for (k = 0; j >= 0; j-- , k++)
				{
					for (lic = 0, i = n1_len;  i >= 0;  i--, lic++)
					{
						(*(result_p + k + lic ))  += (*(number2 + j)-48) * (*(number1 + i)-48);
						if (*(result_p + k + lic) >= 10)
						{
							multipler = (*(result_p + k + lic)) / 10;
							*(result_p + k + lic) = (*(result_p + k + lic)) % 10;
							*(result_p + k + 1 + lic) += multipler;
						}
					}
				}
			}
			else// number2(j) longer bigger or same lng
			{
				for (k = 0; i >= 0; i--, k++)
				{
					for (lic = 0, j = n2_len; j >= 0; j--, lic++)
					{
						(*(result_p + k + lic)) += (*(number2 + j) - 48) * (*(number1 + i) - 48);
						if (*(result_p + k + lic) >= 10)
						{
							multipler = (*(result_p + k + lic)) / 10;
							*(result_p + k + lic) = (*(result_p + k + lic)) % 10;
							*(result_p + k + 1 + lic) += multipler;
						}
					}
				}
			}
			//for (k = 0; k < size; k++)
				//printf(" %i ", *(result_p + k));
			//printf("\n");
		/*	for (k = 0; 0 ; k++)
			{
				if (*(result_p + k) >= 10)
				{
					multipler = (*(result_p + k)) / 10;
					*(result_p + k) = (*(result_p + k)) % 10;
					*(result_p + k + 1) += multipler;
				}
			}*/
			//	printf(" %i ", *(result_p + k));
			k = 0;
			while (k < size)
			{
				(*(result_p + k)) += 48;
				k++;
			}
			//for (k = 0; k < size; k++)
				//printf(" %c ", *(result_p + k));
			k = size-1;
			while (*(result_p + k) == '0' && k >= 0)
			{
				*(result_p + k) = 0;
				k--;
			}
			
			
			for (i = 0; i < k; ++i, --k)
			{
				j = *(result_p + i);
				*(result_p + i) = *(result_p + k);
				*(result_p + k) = j;
			}
			
			return 0;
	}
	else if (*number1 == '-' && *number2 == '-')    // dwa minusy = plus
	{
		int i = 0;
		int j = 0;
		int k = 0;
		while (*(number1 + i))
		{
			i++;
		}
		while (*(number2 + j))
		{
			j++;
		}
		int size;	// wielkosc pamieci
		int multipler;
		size = strlen(number1) + strlen(number2);
		*result = (char *)malloc(size + 1);

		if (*result == NULL) return 3;
		char* result_p = *result;

		while (k < size)
		{
			*(result_p + k) = 0;
			k++;
		}
		*(result_p + k) = 0;
		i--; j--;
		int lic;
		int n1_len = i; int n2_len = j;
		if (i >= j)		// number1 longer bigger or same lng
		{
			for (k = 0; j >= 1; j--, k++)
			{
				for (lic = 0, i = n1_len; i >= 1; i--, lic++)
				{
					(*(result_p + k + lic)) += (*(number2 + j) - 48) * (*(number1 + i) - 48);
					if (*(result_p + k + lic) >= 10)
					{
						multipler = (*(result_p + k + lic)) / 10;
						*(result_p + k + lic) = (*(result_p + k + lic)) % 10;
						*(result_p + k + 1 + lic) += multipler;
					}
				}
			}
		}
		else// number2(j) longer bigger or same lng
		{
			for (k = 0; i >= 1; i--, k++)
			{
				for (lic = 0, j = n2_len; j >= 1; j--, lic++)
				{
					(*(result_p + k + lic)) += (*(number2 + j) - 48) * (*(number1 + i) - 48);
					if (*(result_p + k + lic) >= 10)
					{
						multipler = (*(result_p + k + lic)) / 10;
						*(result_p + k + lic) = (*(result_p + k + lic)) % 10;
						*(result_p + k + 1 + lic) += multipler;
					}
				}
			}
		}
		//for (k = 0; k < size; k++)
		//printf(" %i ", *(result_p + k));
		//printf("\n");
		//for (k = 0; k < size; k++)
		//printf(" %i ", *(result_p + k));
		k = 0;
		while (k < size)
		{
			(*(result_p + k)) += 48;
			k++;
		}
		//for (k = 0; k < size; k++)
		//printf(" %c ", *(result_p + k));
		k = size - 1;
		while (*(result_p + k) == '0')
		{
			*(result_p + k) = 0;
			k--;
		}
		
		
		for (i = 0; i < k; ++i, --k)
		{
			j = *(result_p + i);
			*(result_p + i) = *(result_p + k);
			*(result_p + k) = j;
		}

		return 0;
	}
	else if (*number1 == '-' && *number2 != '-') 
	{
		int i = 0;
		int j = 0;
		int k = 0;
		while (*(number1 + i))
		{
			i++;
		}
		while (*(number2 + j))
		{
			j++;
		}
		int size;				// wielkosc pamieci
		int multipler;
		size = strlen(number1) + strlen(number2);
		*result = (char *)malloc(size + 1);

		if (*result == NULL) return 3;
		char* result_p = *result;

		while (k < size)
		{
			*(result_p + k) = 0;
			k++;
		}
		*(result_p + k) = 0;
		i--; j--;
		int lic;
		int n1_len = i; int n2_len = j;
		if (i >= j)				// number1 longer bigger or same lng  *number1 == '-' *number2 != '-'
		{
			for (k = 0; j >= 0; j--, k++)
			{
				for (lic = 0, i = n1_len; i >= 1; i--, lic++)
				{
					(*(result_p + k + lic)) += (*(number2 + j) - 48) * (*(number1 + i) - 48);
					if (*(result_p + k + lic) >= 10)
					{
						multipler = (*(result_p + k + lic)) / 10;
						*(result_p + k + lic) = (*(result_p + k + lic)) % 10;
						*(result_p + k + 1 + lic) += multipler;
					}
				}
			}
		}
		else// number2(j) longer bigger or same lng
		{
			for (k = 0; i >= 1; i--, k++)
			{
				for (lic = 0, j = n2_len; j >= 0; j--, lic++)
				{
					(*(result_p + k + lic)) += (*(number2 + j) - 48) * (*(number1 + i) - 48);
					if (*(result_p + k + lic) >= 10)
					{
						multipler = (*(result_p + k + lic)) / 10;
						*(result_p + k + lic) = (*(result_p + k + lic)) % 10;
						*(result_p + k + 1 + lic) += multipler;
					}
				}
			}
		}
		//for (k = 0; k < size; k++)
		//printf(" %i ", *(result_p + k));
		//printf("\n");
		
		
		//for (k = 0; k < size; k++)
		//printf(" %i ", *(result_p + k));
		k = 0;
		while (k < size)
		{
			(*(result_p + k)) += 48;
			k++;
		}
		//for (k = 0; k < size; k++)
		//printf(" %c ", *(result_p + k));
		k = size - 1;
		while (*(result_p + k) == '0')
		{
			*(result_p + k) = 0;
			k--;
		}
		++k;
		*(result_p + k) = '-';
		
		for (i = 0; i < k; ++i, --k)
		{
			j = *(result_p + i);
			*(result_p + i) = *(result_p + k);
			*(result_p + k) = j;
		}

		return 0;
	}
	else if (*number1 != '-' && *number2 == '-')
	{
		int i = 0;
		int j = 0;
		int k = 0;
		while (*(number1 + i))
		{
			i++;
		}
		while (*(number2 + j))
		{
			j++;
		}
		int size;				// wielkosc pamieci
		int multipler;
		size = strlen(number1) + strlen(number2);
		*result = (char *)malloc(size + 1);

		if (*result == NULL) return 3;
		char* result_p = *result;

		while (k < size)
		{
			*(result_p + k) = 0;
			k++;
		}
		*(result_p + k) = 0;
		i--; j--;
		int lic;
		int n1_len = i; int n2_len = j;
		if (i >= j)				// number1 longer bigger or same lng  *number1 != '-' *number2 == '-'
		{
			for (k = 0; j >= 1; j--, k++)
			{
				for (lic = 0, i = n1_len; i >= 0; i--, lic++)
				{
					(*(result_p + k + lic)) += (*(number2 + j) - 48) * (*(number1 + i) - 48);
					if (*(result_p + k + lic) >= 10)
					{
						multipler = (*(result_p + k + lic)) / 10;
						*(result_p + k + lic) = (*(result_p + k + lic)) % 10;
						*(result_p + k + 1 + lic) += multipler;
					}
				}
			}
		}
		else// number2(j) longer bigger or same lng
		{
			for (k = 0; i >= 0; i--, k++)
			{
				for (lic = 0, j = n2_len; j >= 1; j--, lic++)
				{
					(*(result_p + k + lic)) += (*(number2 + j) - 48) * (*(number1 + i) - 48);
					if (*(result_p + k + lic) >= 10)
					{
						multipler = (*(result_p + k + lic)) / 10;
						*(result_p + k + lic) = (*(result_p + k + lic)) % 10;
						*(result_p + k + 1 + lic) += multipler;
					}
				}
			}
		}
		//for (k = 0; k < size; k++)
		//printf(" %i ", *(result_p + k));
		//printf("\n");

		//for (k = 0; k < size; k++)
		//printf(" %i ", *(result_p + k));
		k = 0;
		while (k < size)
		{
			(*(result_p + k)) += 48;
			k++;
		}
		//for (k = 0; k < size; k++)
		//printf(" %c ", *(result_p + k));
		k = size - 1;
		while (*(result_p + k) == '0')
		{
			*(result_p + k) = 0;
			k--;
		}
		++k;
		*(result_p + k) = '-';

		for (i = 0; i < k; ++i, --k)
		{
			j = *(result_p + i);
			*(result_p + i) = *(result_p + k);
			*(result_p + k) = j;
		}

		return 0;
	}
	else
		return 2;
	return 2;
}

int calculate(const char* expr, char **result)			
{														
	if (expr == NULL || result == NULL)
		return 1;
	if (validate_expression(expr))
		return 2;
	int number = 2, //1 = number 2 = math operator 3 = number minus	- NUMBER
		action = 1;//1 = add    2 = minus         3 = multiply     - action
	if(add("0", "0", result))
	{
		return 3;
	}
	char *buf=(char *)malloc(10000);
	if (buf == NULL)
	{
		free(*result);
		return 3;
	}
	char *buf_r = (char *)malloc(10000);
	if (buf_r == NULL)
	{
		free(buf);
		free(*result);
		return 3;
	}

	int i,j=0;

	for (i = 0, j =0; *(expr + i) ; i++)
	{
		if (number == 2)
		{
			j = 0;
			if (*(expr + i) >= '0'&& *(expr + i) <= '9')
			{
				number = 1;
				*(buf + j) = *(expr + i);
				j++;
			}
			else if (*(expr + i) == '-')
			{
				number = 3;
				*(buf + j) = *(expr + i);
				j++;
			}
		}
		else if (number == 1)
		{
			if (*(expr + i) >= '0'&& *(expr + i) <= '9')
			{
				number = 1;
				*(buf + j) = *(expr + i);
				j++;
			}
			else if (*(expr + i) == '-' || *(expr + i) == '+' || *(expr + i) == '*')
			{
				number = 2;
				*(buf + j) = 0;
				j = 0;
				strncpy(buf_r, *result, 10000);
				free(*result);
				if (action == 1)
				{
					if (add(buf_r, buf, result))
						return 3;
				}
				else if (action == 2)
				{
					if (subtract(buf_r, buf, result))
						return 3;
				}
				else if (action == 3)
				{
					if (multiply(buf_r, buf, result))
						return 3;
				}
				if (*(expr + i) == '+')
					action = 1;
				else if (*(expr + i) == '-')
					action = 2;
				else if (*(expr + i) == '*')
					action = 3;
			}
		}
		else if (number == 3)
		{
			*(buf+j) = *(expr + i);
			number = 1;
			j++;
		}
		//koniec wyrazenia wykonaj obliczenia ostatniej liczby 
		if (!*(expr + i + 1))
		{
			*(buf + j) = 0;
			j = 0;
			strncpy(buf_r, *result, 10000);
			free(*result);
			if (action == 1)
			{
				if (add(buf_r, buf, result))
				{
					free(buf); free(buf_r);
					return 3;
				}
			}
			else if (action == 2)
			{
				if (subtract(buf_r, buf, result))
				{
					free(buf); free(buf_r);
					return 3;
				}
			}
			else if (action == 3)
			{
				if (multiply(buf_r, buf, result))
				{
					free(buf); free(buf_r);
					return 3;
				}
			}
		}
	}
	free(buf); free(buf_r);
	return 0;

}