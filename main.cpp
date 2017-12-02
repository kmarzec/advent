#include <string>
#include <sstream>
#include <cassert>
#include <climits> 
#include <vector>
#include "windows.h"

void PrintDbg(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    char buffer[1024];
    _vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, format, args);
    OutputDebugStringA(buffer);
    va_end(args);
}

int IterateAndAddIfDigitWithOffsetIsEqual(const std::string& input, std::string::size_type offset)
{
    int result = 0;

    for (std::string::size_type i = 0; i < input.size(); ++i)
    {
        char first = input[i];
        char second = input[(i + offset) % input.size()];

        if (first == second)
        {
            result += (first - '0');
        }
    }

    return result;
}

void Day1_1(const std::string& task, const std::string& input)
{
    int result = IterateAndAddIfDigitWithOffsetIsEqual(input, 1);
    PrintDbg("Day1_1 %s: %d\n", task.c_str(), result);
}

void Day1_2(const std::string& task, const std::string& input)
{
    assert((input.size() % 2) == 0);
    int result = IterateAndAddIfDigitWithOffsetIsEqual(input, input.size() / 2);
    PrintDbg("Day1_2 %s: %d\n", task.c_str(), result);
}

void Day1()
{
    std::string input = 
        "3294199471327195994824832197564859876682638188889768298894243832665654681412886862234525991553276578"
        "6412655899591784142183893293614966739916146736263445521794139955622668181383723932139661431249144693"
        "9769258725111266321786287923322676353391112889335453635321384712225146385789415981982872482796957643"
        "2191847787772732881266875469721189331882228146576832921314638221317393256471998598117289632684663355"
        "2738459839338457217134978117669953677958579652221836687655174542633541111348413346313451115961316827"
        "2619657476316518788933759958334563441343616553974418886615677158564771855518252993666968358166239861"
        "8765391487164715724849894563314426959348119286955144439452731762666568741612153254469131724137699832"
        "9847289378659567119255926284566171336952595545487193282299386213323251259725471812368122638873758662"
        "3111831295436943293735935726646738331832623957287731476512184483112617817398879976521891317882596626"
        "8816476559792947359956859989228917136267178571776316345292573489873792149646548747995389669692188457"
        "7244144687271928199194482759221663211581413652375452226336883728914518424344585276987743421114824989"
        "9938383149257761515459127871965679827737736328437946875799837319323179576764465415543269298865131284"
        "5433511879457921638934877557575241394363721667237778962455961493559848522582413748218971212486373232"
        "7958783629648738559946971496928249171833755451921194535873981999125644746142199293451854686611299663"
        "7969381349854247473219817649669474611157692571549396729648725823785415238236557987689439181575981537"
        "3319159213475555251488754279888245492373595471189191353244684697662848376529881512529221627313527441"
        "2214596727869231451659896112233722411499294362473748184674816419318729725822954259369985351944239165"
        "4436779952227691444523158227236838883183443756275211932528647435286355469337371884864956845179775192"
        "6315617575295381964426843625282819524747119726872193569785611959896776143539915299968276374712996485"
        "3678534947343762575112734437364334644962872196156973419731317151667689161498283964546385967135729636"
        "86159214116763";

    Day1_1("sample1", "1122");
    Day1_1("sample2", "1111");
    Day1_1("sample3", "1234");
    Day1_1("sample4", "91212129");
    Day1_1("puzzle", input);

    Day1_2("sample1", "1212");
    Day1_2("sample2", "1221");
    Day1_2("sample3", "123425");
    Day1_2("sample4", "123123");
    Day1_2("sample5", "12131415");
    Day1_2("puzzle", input);
}

int GetDiffBetweenLargestAndSmallest(const std::string& line)
{
	std::stringstream lineStream(line);

	int value;
	int minValue = INT_MAX;
	int maxValue = INT_MIN;
	
	do
	{
		lineStream >> value;
		minValue = min(minValue, value);
		maxValue = max(maxValue, value);
	} 
	while (!lineStream.eof());

	return maxValue - minValue;
}

void Day2_1(const std::string& task, const std::string& input)
{
	std::stringstream inputStream(input);
	std::string line;
	int diffSum = 0;
	for (std::string line; std::getline(inputStream, line);)
	{
		diffSum += GetDiffBetweenLargestAndSmallest(line);
	}

	PrintDbg("Day2_1 %s: %d\n", task.c_str(), diffSum);
}

int GetResultOfDivideWithNoRemainder(const std::string& line)
{
	std::stringstream lineStream(line);

	int value;
	std::vector<int> numbers;

	do
	{
		lineStream >> value;
		numbers.push_back(value);
	} while (!lineStream.eof());

	for (int i=0; i<numbers.size(); ++i)
	{
		for (int j = 0; j<numbers.size(); j++)
		{
			if (i != j)
			{
				int first = numbers[i];
				int second = numbers[j];

				if (first % second == 0)
				{
					return first / second;
				}
				if (second % first == 0)
				{
					return second / first;
				}
			}
		}
	}

	assert(0);
	return INT_MIN;
}

void Day2_2(const std::string& task, const std::string& input)
{
	std::stringstream inputStream(input);
	std::string line;
	int divSum = 0;
	for (std::string line; std::getline(inputStream, line);)
	{
		divSum += GetResultOfDivideWithNoRemainder(line);
	}

	PrintDbg("Day2_2 %s: %d\n", task.c_str(), divSum);
}

void Day2()
{
	std::string input =
		R"(798	1976	1866	1862	559	1797	1129	747	85	1108	104	2000	248	131	87	95
		   201	419	336	65	208	57	74	433	68	360	390	412	355	209	330	135
		   967	84	492	1425	1502	1324	1268	1113	1259	81	310	1360	773	69	68	290
		   169	264	107	298	38	149	56	126	276	45	305	403	89	179	394	172
		   3069	387	2914	2748	1294	1143	3099	152	2867	3082	113	145	2827	2545	134	469
		   3885	1098	2638	5806	4655	4787	186	4024	2286	5585	5590	215	5336	2738	218	266
		   661	789	393	159	172	355	820	891	196	831	345	784	65	971	396	234
		   4095	191	4333	161	3184	193	4830	4153	2070	3759	1207	3222	185	176	2914	4152
		   131	298	279	304	118	135	300	74	269	96	366	341	139	159	17	149
		   1155	5131	373	136	103	5168	3424	5126	122	5046	4315	126	236	4668	4595	4959
		   664	635	588	673	354	656	70	86	211	139	95	40	84	413	618	31
		   2163	127	957	2500	2370	2344	2224	1432	125	1984	2392	379	2292	98	456	154
		   271	4026	2960	6444	2896	228	819	676	6612	6987	265	2231	2565	6603	207	6236
		   91	683	1736	1998	1960	1727	84	1992	1072	1588	1768	74	58	1956	1627	893
		   3591	1843	3448	1775	3564	2632	1002	3065	77	3579	78	99	1668	98	2963	3553
		   2155	225	2856	3061	105	204	1269	171	2505	2852	977	1377	181	1856	2952	2262)";


	std::string sampleDay2_1 =
		R"(5 1 9 5
		   7 5 3
		   2 4 6 8)";
	Day2_1("sample", sampleDay2_1);

	Day2_1("puzzle", input);

	std::string sampleDay2_2 =
		R"(5 9 2 8
		   9 4 7 3
		   3 8 6 5)";
	Day2_2("sample", sampleDay2_2);

	Day2_2("puzzle", input);

}

int main()
{
    //Day1();
	Day2();

    return 0;
}

