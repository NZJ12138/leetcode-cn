


//////////////////////////////////////////////////////////////////////////
bool isPowerOfTwo(int n) 
{
	if (n <= 0) return false;
	return ((n&(n - 1)) == 0);
}

//////////////////////////////////////////////////////////////////////////
bool _solution_run(int n)
{
	return isPowerOfTwo(n);
}

//#define USE_SOLUTION_CUSTOM
//bool _solution_custom(TestCases &tc)
//{
//}

//////////////////////////////////////////////////////////////////////////
vector<string> _get_test_cases_string()
{
	return {};
}

#define USE_GET_TEST_CASES_FILESTREAM
string _get_test_cases_filestream()
{
	return "../../problems/power-of-two/tests.txt";
}

