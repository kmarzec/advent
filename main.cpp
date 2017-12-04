#include <string>
#include <sstream>
#include <cassert>
#include <climits> 
#include <vector>
#include <iterator>
#include <algorithm>
#include <set>
#include <memory.h>
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

	for (std::vector<int>::size_type i=0; i<numbers.size(); ++i)
	{
		for (std::vector<int>::size_type j = 0; j<numbers.size(); j++)
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


int isqrt(unsigned x) 
{
    unsigned a, b, m;       
    // Limits and midpoint.   
    a = 1;   
    b = (x >> 5) + 8;       
    // See text.   
    if (b > 65535) b = 65535;   
    do {      
        m = (a + b) >> 1;      
        if (m*m > x) 
            b = m - 1;      
        else         
            a = m + 1;   
    } while (b >= a);   
    return a - 1; 
}


std::pair<int, int> GetCorrdsOfElementInSpiral(int element)
{
    if (element == 1)
    {
        return std::make_pair(0, 0);
    }

    int layer = (isqrt(element - 1) + 1) / 2;
    int layerWidth = 2 * layer + 1;
    int layerStart = 2 * (layer - 1) + 1;
    layerStart *= layerStart;
    layerStart += 1;
    int layerSize = 8 * layer;

    int offsetInLayer = element - layerStart;
    int segment = offsetInLayer / (layerWidth - 1);
    int offsetInSegment = offsetInLayer % (layerWidth - 1);
    int offsetFromCenter = offsetInSegment - layer + 1;

    int x = 0;
    int y = 0;
    switch (segment)
    {
    case 0:
        x = layer;
        y = -offsetFromCenter;
        break;
    case 1:
        x = -offsetFromCenter;
        y = -layer;
        break;
    case 2:
        x = -layer;
        y = offsetFromCenter;
        break;
    case 3:
        x = offsetFromCenter;
        y = layer;
        break;
    default:
        assert(0);
    }

    return std::make_pair(x, y);
}

int GetStepsForElement(int element)
{
    std::pair<int, int> coords = GetCorrdsOfElementInSpiral(element);
    return std::abs(coords.first) + std::abs(coords.second);
}

void Day3_1(const std::string& task, int element)
{
    int steps = GetStepsForElement(element);
    PrintDbg("Day3_1 %s: %d\n", task.c_str(), steps);
}


class Array
{
public:
    Array()
    {
        memset(m_values, 0, sizeof(m_values));
    }

    int& Get(int x, int y) { return m_values[x + 16][y + 16]; }

private:
    int m_values[32][32];
};

void Day3_2(const std::string& task, int value)
{
    Array arr;
    
    arr.Get(0, 0) = 1;

    int maxValue = 0;
    int element = 2;
    while (maxValue < value)
    {
        int sum = 0;
        std::pair<int, int> coords = GetCorrdsOfElementInSpiral(element);
        sum += arr.Get(coords.first + 1, coords.second + 1);
        sum += arr.Get(coords.first + 1, coords.second + 0);
        sum += arr.Get(coords.first + 1, coords.second - 1);
        
        sum += arr.Get(coords.first + 0, coords.second - 1);
        
        sum += arr.Get(coords.first - 1, coords.second - 1);
        sum += arr.Get(coords.first - 1, coords.second + 0);
        sum += arr.Get(coords.first - 1, coords.second + 1);

        sum += arr.Get(coords.first + 0, coords.second + 1);

        arr.Get(coords.first, coords.second) = sum;
        maxValue = sum;
        element++;
    }

    PrintDbg("Day3_2 %s: %d\n", task.c_str(), maxValue);
}

void Day3()
{
    Day3_1("sample1", 1);
    Day3_1("sample1", 12);
    Day3_1("sample1", 23);
    Day3_1("sample1", 1024);
    Day3_1("puzzle", 265149);

    Day3_2("puzzle", 265149);
}


bool IsPassphraseValid(const std::string& phrase, bool allowAnagrams)
{
    std::stringstream ss(phrase);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> words(begin, end);

    std::set<std::string> wordSet;

    for (std::string word : words)
    {
        if (!allowAnagrams)
        {
            std::sort(word.begin(), word.end());
        }

        if (!wordSet.insert(word).second)
        {
            return false;
        }
    }

    return true;
}

void Day4_1(const std::string& input)
{
    std::string sample1 = "aa bb cc dd ee";
    PrintDbg("Day4_1 %s - %s\n", sample1.c_str(), IsPassphraseValid(sample1, true) ? "valid" : "not valid");

    std::string sample2 = "aa bb cc dd aa";
    PrintDbg("Day4_1 %s - %s\n", sample2.c_str(), IsPassphraseValid(sample2, true) ? "valid" : "not valid");

    std::string sample3 = "aa bb cc dd aaa";
    PrintDbg("Day4_1 %s - %s\n", sample3.c_str(), IsPassphraseValid(sample3, true) ? "valid" : "not valid");


    std::stringstream inputStream(input);
	std::string phrase;
    int phrases = 0;
    int validPhrases = 0;
	for (std::string phrase; std::getline(inputStream, phrase);)
	{
        phrases++;
        if (IsPassphraseValid(phrase, true))
        {
            validPhrases++;
        }
	}

    PrintDbg("Day4_1 phrases: %d, valid: %d\n", phrases, validPhrases);
}

void Day4_2(const std::string& input)
{
    std::string sample1 = "abcde fghij";
    PrintDbg("Day4_2 %s - %s\n", sample1.c_str(), IsPassphraseValid(sample1, false) ? "valid" : "not valid");

    std::string sample2 = "abcde xyz ecdab";
    PrintDbg("Day4_2 %s - %s\n", sample2.c_str(), IsPassphraseValid(sample2, false) ? "valid" : "not valid");

    std::string sample3 = "a ab abc abd abf abj";
    PrintDbg("Day4_2 %s - %s\n", sample3.c_str(), IsPassphraseValid(sample3, false) ? "valid" : "not valid");

    std::string sample4 = "iiii oiii ooii oooi oooo";
    PrintDbg("Day4_2 %s - %s\n", sample4.c_str(), IsPassphraseValid(sample4, false) ? "valid" : "not valid");

    std::string sample5 = "oiii ioii iioi iiio";
    PrintDbg("Day4_2 %s - %s\n", sample5.c_str(), IsPassphraseValid(sample5, false) ? "valid" : "not valid");


    std::stringstream inputStream(input);
    std::string phrase;
    int phrases = 0;
    int validPhrases = 0;
    for (std::string phrase; std::getline(inputStream, phrase);)
    {
        phrases++;
        if (IsPassphraseValid(phrase, false))
        {
            validPhrases++;
        }
    }

    PrintDbg("Day4_2 phrases: %d, valid: %d\n", phrases, validPhrases);
}

void Day4()
{
    std::string input1 =
     R"(bdwdjjo avricm cjbmj ran lmfsom ivsof
        mxonybc fndyzzi gmdp gdfyoi inrvhr kpuueel wdpga vkq
        bneh ylltsc vhryov lsd hmruxy ebnh pdln vdprrky
        fumay zbccai qymavw zwoove hqpd rcxyvy
        bcuo khhkkro mpt dxrebym qwum zqp lhmbma esmr qiyomu
        qjs giedut mzsubkn rcbugk voxk yrlp rqxfvz kspz vxg zskp
        srceh xdwao reshc shecr
        dcao isz wwse bbdgn ewsw qkze pwu
        lbnvl lviftmr zqiv iadanl fdhrldn dlaani lxy dhfndrl fkoukx
        raovmz pdysjsw hqps orsyqw rrwnzcz vrzoam jjljt
        wgt gzi icpwp qeefgbe msadakj jbbrma sbj dufuujx zex
        cfzx bvyu eswr hafcfy klw bgnhynv qrf aop
        rzlq atrzcpb hpl pajjw cdxep ean aptzcrb rzcbapt
        xogpf ucc nsukoz umtfbw xfvth ozusnk fopxg ubp iflb
        xot nqcdyu kpwix szo cyxv hpmp hwtrc zso nyuqdc aha
        mkzf cat tkjprc izxdggf obspan lmlbg bsyspf twox
        lfmfrd ooclx tcl clt
        dxvnyd nxwojj arutn eyqocj swzao tmh juvpezm
        teu eman rlmdmk xkbodv fvrcm zorgy wmwe
        hmo fdayx duciqf cgt duciqf
        imjnv vfmsha cyrusow xjswoq nclrmjy sjxowq ynjrcml
        rwbsay alsi bmzpvw ozq aduui nihwx glwdiz ixmkgfx
        vtjzc ntkh zekj qrbkjhn zekj lyfnbg
        afaig jqhli oie lhwyduh kqfnraz nfrzaqk mayfg iljqh
        inb zum zmu dnl zjxg vrdziq ypdnsvt
        uhbzmre mpdxm alkbmsq aopjmkl mqxenry ayvkrf zxvs qkfqva
        fimjr ccv cnug crdsv
        bqyve lhxdj ydu qbyve vihwjr vyodhc
        vmng dyttyf noagpji tdtyfy ewiest ogg
        kgscfj klmsv vmksl vmlks
        qlvh veo wruft wtm fbrlvjr evo wvwmny dhp bvrlrfj lvt vgzuyyw
        mxuro orxmu tivu tjdq ojjvju cdd
        kjexme gxbysxp yxrum hinrklv fxehytd qkt tqk umryx nim
        kywnux wab tzrft dsaz jgwuw dubarmi fle wjguvr umjp uzncwj mzz
        qokwh zrda xywufk tbxhhj eejqaoa hwoqk zer hwt hbjxth xyf hmh
        eregs qdx tdequa agrlrg mwwpba qjie yrjvhr txujk
        iyot fxwdcb zvwfv vfzwv wvkw ncwbr wdejrr ltcdza
        waix eza znmonya ldfghws ialwfvc dey ubsz uhbnh svgekg nonzyam
        bryz tfbqn xznfmw xiplgww wwxigpl jxzcgxl rzyb
        cqvl rrcoqxs staeuqr hzzow cwv tsvol dio coc ddavii uuojy
        txbn qvkkyh gbqnjtq ndpkqr srt bkpqfmm ytycev ypcv bpqmmfk
        uqkjmul dour zgq ztango yrrjhrg ufxnmuw
        ekxbcv vkxbec xbcevk jiq bar
        wczff qdu cwffz hhk wlvyg
        zjlconc osgsro dajzo hqih ehml
        hnio shccluw cpu ivaby tormn vkef abv vkef ivaby
        xgbdeso xiizs omqwy sbtnnt khago evviclw xyu dtvg wsyxfuc humewp
        cnzu bia vdyqrf wwb qveum hmh ouupgc owli
        pjpmfxa dvd lxgh ndy gwph oebfkqv vtlxdg efl ekj dyn
        mvan nmdkc ucyshia mavn ecst poo
        oybm pjwm bmyo wovgu xykziaq obmy eiirhqd
        xkvomx yxvv oxxpth elh vxvy lhe ycn
        okxglw gmaangx gnxaamg yduzrr nzwxtnd rcxcu xjjvno yat cin gaxnamg yss
        oicgs rrol zvnbna rrol
        abb edpnxuo peoudxn bab ceay
        ncpkfz gvwunb fckpzn caafx pkcfzn tsfl
        fnrt ymenkpq wodubcm niv nvi ziluu cuowbdm zocg pdakwt mlzxkex nuxqclo
        uouxcgl stgua otadr ideannq wizxunv iqsdpj mxddt ldst ucxogul
        rbrwyhk wqoz zqwo ikwgexl atpu iza
        smo yolp pcahlu muljxkq cbkljmz zlbcmkj zvbmgz eaiv ncv zplifm yplo
        ocutdhz zmnaap llgv llzpl loavju guzkfq saay rxyhng cwxzx lcv anrnzs
        etyzx tcm upxrtvd imyoiu rdpj fed dmm
        gonqa szteh szteh razdqh phyff upf knfqfaf knfqfaf fpsgl kakag
        mcju mixskop isrwat lcr nfyi lcr aaevr nfyi pqrbk gnful
        xfmr fkmnq fbnhd mxrf litniid xbae frxm zcenf
        yuh lzojtj rqsh hyu
        vbjgql yeshsuv lokt efqota wpwjfu ykyq rxc fxxh ycqfkk gndts vdf
        wnylmr kkuruxm azr xukrkum dohkwx dmdb
        bjiyrwf dvf fdv vdf gnokekr
        jsaq hcww iayqtu llv gdpxdrd hwlo nosjit wpm lcab fcgwr
        fxjp bys nnf xzllckh bys hvojw zcwtgwz wye ccyvjv
        grafa hbb ghk wkdpsf ufa uoqmysd
        yvacf kssbff iovrm mvrio cfbpb avh zzje
        gqd qmsen wkvrfz vhtsa zrwfkv gul zkvwrf
        hrbi svaogb aogsvb bgrk hibr jbtkr
        ljl ryc mrewrge yky
        fcqyymt emk qcmyytf mcfvusb luy qany cbsvumf
        oknt mcozuc ccmuoz uoccmz
        uziil xobutwf acnof iqgwl diso
        sekq fxbtsuv ddnnqg rnemlt dngnqd hhgjfus stxvubf
        lajcp qgiw fyz blrlcd pviwv buh wnkk
        wolqfk nvpapfc rwcqxfz xobno yzjfz irpj wolqfk wbnwjt
        vmabj noiljne hhqf holxkbk swwzx ylgj lnmxy lqodhk abjvm bmsrf
        bpnp yrz pjepxxs jlmhuy vihlx zacm inuazhc xsxjepp
        tryl kryh eonvaad ucevssk umkxg lqej nswopjj svkeucs bmh stosxxz
        cfdwd dmfdrvm ibuhsz nwtgmb pjt dmfdrvm cqdcm fzjjz afa ibuhsz
        erwp abn jwx ynmkkj rhgg abn epd atqhs rst rhgg
        jtnp cegdsoy gfuvfbg gdmn ahlsc
        jgrp diu jrgp onjnml nojmnl vxockc
        lakqyuw khq dcpiwt ykwlqua hkq plklx ujbckec hjcvur jnp pvyf
        usuvoo jkih ylafyy yhio jureyj
        uazisdf cnwlfnf ewodatr woaddkd wbla qmn atdrowe
        bnyepaa ntqh xppe ydtsw ppex
        yewjwsp jxylmtk ijese ewry ijese kbja nfml zeuwcsh juimz
        qbvmf nca zsfreo uurgaiz twe fbqmv ncwi etdcsk atowfp
        jeotslx kgdpzp wxlcww pdd dcn ddp
        macllv ldl kyluine lbt hbxbr wxcaspp ezwvc qxkeu
        ivg gxv zsf ucr uff yrz
        tdlwbny bqlrlz tbynwdl lwtbdny
        tnekq pdaievs ttwpfh xfm fcaa
        zqqhl zbf fbz uqrv bfz ffwavhk foccg
        vcw ebqdd cwv eddbq nrmq
        hpiusz sizphu xzq sgyehk wgagkv hsygek
        vagkxa iou frqdnnr ipcg uxvh vvh eskf katgpiq aqktigp gzvseyi
        xkwgd kzfxk pgdy fmtvq ngf rshx zti pamviob ely knz
        hwo rteohu qzwoe rotuhe wzb
        bsqgg tid dti gtats dit
        sjtux djwxv dljwjq xwvjd xnqfvx veqdrtl uxtsj nnkjn wnhilaf unirrp
        fruuqjk gtote gooklg bzwhim zfnccmm ezipnf cxwdxa wfu fdca
        zcyxb byzxc cxbyz pgcqco ivlxz
        wrjh zfdinsf ihw xwosiah hdg xpiabno bilyy azdeczg javuwa
        rinlv dcpt qhencba mmb njxw gadc
        qwcpua qzyzt cxjsgh kumh byiimas qhsgf qytzz rqqruwp ismyiba xydcxz rwkscqa
        xbzefi hltca ibzxfe fkx xizbfe wvaynts
        oyuce vzk ouxvj gfh efgbv ubc nyb bxnbhd mtwboe whksy ovmrt
        ljrebp tacn bpjler utphw wmfw rcnha
        drdnic eyodes rcnidd yseeod
        umxmsf kfroz ukhjin awpnnnu ooyyohh tuv rafano jze
        bakz lfzpjyg gfkqcgn kzh zwpvk gqfngck
        jpaony ojpnya hmro xaaz tovary aaxz iel pbg
        swvbgc bbhjp yvrcddd rhj clfu eao afrkegn qvvb yvcx nxjmdo rcvtx
        conbjy jeqtri wvujt jeqtri rkhllgw tsdt zowreo qxr qbpragn kuzmplw wvujt
        jrpxyp hchljy rkowqb eeaf ltllebb gtksrwx iazx vnsfmc zzrxw hlcjyh
        piehb cjdzt eqn kuje rls oaewoz lrqwt lcrrq
        hdjowxv uknhlv hluknv pokxg
        txiqxfr fyyp pyyf xfxtrqi tvm rtvby cfx trx nwrf kqrxtat alwot
        wdaadr stexpow ardawd uejqxc
        wwgwjel wwgwjel mtjt wwgwjel
        mczx uua lgceb dqru vkcea tcet ruz
        jkt yroojr qdrtdu wze ovwz fdmqnr xxsyfd kchytwl hctlkwy gyd
        eif irnrce iamhxgh bmis uxye azrwdi sznv yuowb vdlqqxu
        dxdjyj hngqwzs yhwku qhsctfe rhbc rchb tqhcfse
        fxyxnzs qtxevin rvtxtc iqnxtve
        zgbpk mwzxx bgpkz wkpkn
        rjiym iub lcyw agbtlb bzhx osv rbtf
        emmyu uoflio tinih skpqaj rbor gezbhhv ine mij qlqte uuj ycns
        owmwc uhxv pyho ftjh jzsg blqn bszyo bob trbycy mkru
        mwgz bbqsmpp fgzs bihhg bbn pjxxexs qrqmt htsxfwo qltqp vqqaxi
        lpr wcvy sxjqq ltd rftdgv pdnog ymu
        qhcos shuy icdhucu lrikh rwslv yxbgibl rcomhn wakirz
        civdmee owlzocl vedecim rogmjnn pix pohcmk dsjm yworm
        vzdpxp lvt inufv yofqt omm qfoty qrlseqy amkt kjcvg vgkjc
        huhq quhh levzsws sjuun ofgqr cjhp nfxbbft rnt wtbd tbzab
        tjftkx xpfcv hvftvhw lpypbjg batrn fhwhtvv uthl arbtn brb sthv
        ogr uyuxdco bpjgir edztxv sxtgu jzfmx ihnauz zwegqkr kvkw
        mhxthf pervvn gshy jig ezjteq ckkcpy gww
        tiljyki rpe prcojy tjkylii moxu
        pjsdqc lgqydfd lohck emrtejw axwmo wuuv rfi qzyncmw gjijdfb bljfd xrs
        ywjab gynzi relf kziy xmsby izyk ocwoho kqnyh bwayj
        bhjlz uonz jhmzuq eiajoos zjnbj tomj bmyv hjlbz fgw jjbnz
        kszz xzw xzw prtznyb
        ghzk vxhwt thxwv slwpayp qxegmi dawdwo kgzh
        ibpcvuf wnuwxu sbf jsj bfjynl cdp jbylnf
        epaxr vfhf hvff azepadz pwf sbo pgfzya hslyo rqqj rmklw hwtta
        yyolko pwbvxvg xdwl yfje hftep kzzsr kho jeyf yvslxpw kfyv
        xmk juyjxy eqno mdwklum reg dgn cirh wmxfyj bnxlgo dlobk
        oyv gshqyot jgcqe dsf gyohqst gqgeojo egoogjq dmqpyp
        sypianq yss lmhu ulmh itilh ndkda lhiit
        qbxxl bxxql ikald nfap qixwbqq
        jtqhqty ljysnl nwoj toa bmmyj pal
        ahktew sxody nkvsf pbxyt baws wgwfwej bevgzm jus hcvajfy kzrb jwgwewf
        jzsb szbj ujngwf nfuuf lfiuxdu uufnf orsy
        vgo hto isstyul gau wsmxoqw
        uxw itwf epaw hec wape hemol rpwyosc xzxmrll eetz zui kagca
        mjncux muv rygdeis rygdeis
        qgkqjvf iprzibd fkvqqgj llcrl vbh vlf lllrc zwrunt
        dslsa wvoex eqbwj tjem gbx ayn xcan fnacl xggxon gnwjlh
        yzosv hcxjiz yvon gcgd
        bixpny ecln sda eymt bjiwk
        rlcad lrdca adoqfzs rgty mds pwb kmwj
        wkai pmryffq rrdmodc wgyx taz yxwg nkap
        auynzwc vzg uapdv qkrh
        ldmuysp oyu kpn ejbl mfifa bzs hwyn brlw qpzqx uyilao ysdumpl
        czoxoj pwnultl wezolbw lyk aonesgb
        nqy nhb nle yycp lgtbo ojf dytwyh ufa
        rwr eph obg peh pejret prjtee ovgz
        vdqf vdqf ycjrg ovzl lelbe vdqf
        gvagdqm gvdgqam dmb zaxe nepzwn
        emwh bkkbgec qwdgk mhvfsrf wmdfpp ekzuua
        mbqw lgkyazt ckyhvnq uladwo owt
        qwiwd pbo tkjoqda zapo dygqopv zzdlwfn
        qty dhb iinncba ytq kvh idgoevt chx waq
        ulffsvk vplsz ulffsvk uxsh cpwgxd ikgcacx nrirke uowcjvn
        gknmxr grkxnm fco dilyyj grmxkn
        saqxkh uhue nvu fef xsuxq ekyyoc bcaavd
        qltwqa vrmpv vhra nof yprauc vkreojm eaq igiy mec
        wvheiyg uthy gpvcs nhnjrne mqaejr tfnsly zfbhn entcc nystfl cpq
        zxv jzk dwsjgrd gqqxhp xqxu naunwc yeh qzpkz awcnnu aoosa icadax
        vpmqmg qmvpgm tqs mvpqmg
        inehzu zwxeoy jxia fcyzxc hwikd
        bzwnp kamsen ajpn kdls bzh xqcb bzwnp cmjnfa wmgx
        hbuhc qgvhxy smzkxh zzebox hbcuh net wyrdppc yvgxqh
        oeum oemu iyags xaipdi euom
        tqljgoq ghtdhw xhnni lux qltojqg lki zxztda pcqjif acpzvwy
        ydijaq kbyjxpu onyd hsfgz geqvbg
        rwoih xog dtbzyr ryzbdt tdbyzr
        vcdxf zosw pardxfz bmb mscmain lwfc jvq hbszcqh fxomsmm ahnugx
        zutsemg pqzil ddv nsstz gmeuzst bedvy xkzzjpw xlqbd
        xxf ltnnu yeb hbml agj meovtjr qrul kexerkw xxf
        tqrpd hhcx bmdv nlmr pnu pajdtc rpatqi yekedx oeiuew epsshog
        ttbfpv plairk toh jagfsg njnqpa tmwh vwqp irtxv
        vdky uwc tkkkztp vdky vdky qlcw lza
        rzie yundymy pwgx wtwtbg kpiw mewnb liveysj uvsbn
        jgfvyny hacg pzra arpz uowswu puzsfu hoe heo vrq naup
        hqv vrl uko qgpikho lligvxa wdld qgpikho
        whvby yomxwj dieffc jkprinh dsaqy yfrnba woyq yexeb mjn cbszn xeswvvo
        wowtgu rciyg rlas bra quyfec ihe thuu asxhscu bsbdpbi ogxosu
        vydsaet tvnkjq piedkzj foeiqz zqivt iatsju tjnqvk drauaf vqitz invoz
        cppn jqzw zmxr qksuas iifmjg xtkgf cppn cppn jpsd
        nkifpsq cxdx bokxhm ebww kghagrp bofhrl grc cheuzyj
        ibgrlvm hrcx jjuoh ipmt
        hcoqkh fzt rgravb cimauj jxjq blct qhc vjxw pqpg qzp
        jycxz xcv czxjy vxc
        liljaur cgmg neldxb xfummcq yfhiukd dnqhl iolxn cmewhb
        hpvoihj fkwokod txy uuktw vmqqb dpldzh yxmcay cyaxmy xycaym wekr
        ccnaf wuxc ecadb vbgpt ccntf sezo skjdkbf fnctc
        hqdtwho kdhyman bjtcjvr bwllva ncyffyr
        xprn jrrvmj pdw yvexm ewbflbe eapml rvrmjj xmevy rxyzhf
        wjcbpy qdgtcp cfjh muww fhg sgfdleo nelpte yucqa aavev
        rci vqypsqt xmg rzii
        gramh wwprtc ampdhw dajr
        ovrm mdyhpbl mdylbph aykz
        cbmo fxs nuugu guunu upt ljjuhjw nituh utp kxqc
        rhabal rhabal rhabal vah lfrs
        nrq qway ftzp rtjcks mbygdtd hsiqbh wypqb rtjcks cllp hsiqbh
        ywa anhcf nvd puqkwg molrwck wsctx xvd molrwck
        wox jzq jfen wcvus cswvu oxw irg lmu tpj viahm jesic
        qenad neqad smlgi ydwzq ppdemvs ucyuf qtunm eoqx jlgv
        sucpl nrdwbl ltvetok npbw ozzw hafyay sjmui sjmui jkqlq pyn pbuopx
        nxgaiu ybyl meo kgh saqjaz xhbqr otelcyp vkwc
        iqrl ldjlwvl ajhrl dnhutr gkknyqs mcvluet fgyu ogiz cxo aiunl orb
        psd cyq xpoyqny yqc kozqh vonfd uhozwz pds hcpw
        tvaxder tulwmw qiw avddbmh irog vynjzcc refx efxr emnvk
        myjx npqk whm egw kpy igrrohg ukglx ldnuqw caqg ynx fckhnsh
        dafv bkdoqg zcqvbco xgikoac cvbqczo
        rtzhpwk ukuyp bayhzp upkuy ahbpyz
        oarcuv pnlkxvw fqdkj hwzsz nauwl lpufibz vzfbgc unkluxy rwh xuknuyl
        vxhsaj ppdxw qrswqtu ulwv uqtqwsr ppxwd
        cww cww cww scu
        wiiikwa bfpewt zbgxfkl iqpk tpbwfe aazdcxj ipqk icggn fwn fjr
        net ovxuwpz yvzmzd yvzmzd
        xgar czuhp vuhisaq fgrqxy evvrtf mnmar lsk
        hld mxuedug itswju vmmejqx snzslqj toe bbmugph mgubhpb mowj nrjnzu
        qbz ouhye hsldmp lcf hyhlrb ewvle zko
        cke mupaq quapm eck
        owu zdt lales tzd apjjo fhpx bmuktbw dvehpz
        libvl zxypk azazc vtsom ohdzycb
        kiowxnc scxygrf ckxnwio ycxsrgf
        vcjj fqz lfawfx mps zhv qykch vhz psu zud spu fnpvkx
        scfvum fuktgk tua ieosetl wwmjtt exnsw wwmttj plvd pfb kku pdbom
        wkfw snukd wkfw gyaojdf bjw htagy cdsp
        beh gatqxcu ibrooxr ssww orrioxb eenkqz
        jlv affah mtbemf tylh aafhf
        zqfajd uwzrw csouuip qzadjf
        gsnlrw tcel hha tfbzrp ild aenqa
        iirfxef kdux yvj vbzgj
        ibx pfll rgkp nancij llpf xib gbkfy
        uvw kkbavj pznsnk okigtxl ogitxkl eobbs xhaz wroabn ltogxki
        bivdf lotvmoh vrb kpaeeue tdab qhukcb qmy kuqf kesu
        egs hbsfeu esg twxko uib
        ocraimu qilp ijmx eco nhevqp juxf ksejr bcqqau uhpt
        pyx jmpglf juokd dxszjw cml vcjge pfg
        gxwrt btmimse dkpbha idmz mtignka ngakmti
        dpjhm jyalra hukf imocr lkgt rqywn quhe fukh
        nbau xyc bdh yni xaawxm cyx xwaaxm akx gyodqe htbifc
        bywdxe bfrp rvb rndl onal jghiwb nuta aint qlciwcx
        fpic yrqce land soxhci qzc zoebsq hcdohcc fzhcl iyxb dqinum hchdcoc
        zok ghgp zok lmk
        ozfz zofz dkdekzb sqc
        gfti zuqvg cexmtyl qwuqnj stepb erduqhy cuoizcs qudyreh kqvfdd guzqv
        jrugz jzugr lmqu jgihgo hjfbz duxkn unxkd
        ckiys dbqmi ckiys ckiys
        iylp uvvdp pluifaa djo
        esxec rwvel djxppqf jymwt ilm aiz upn aiz wrfefwi rwvel
        nitgjr pokxuy puhdwg qtxpb veylp zqvzkbd lrvpcgu zuy rnigjt ibci
        jboyzq ogcldr hlon ywav jqqtz qjzqt vyaw cok
        aqdw jxn hqknh azbylg
        jya qpxtmsj hqrtsgg qjtpxsm
        pofcs sxw dlvru dlvur swx
        yphvvb qqyyfsp sjkbff dqyerxe jxzes oof
        pwbya txk bbwsj ywgimd kmdpc bawpy lbnt
        bkbazff ldmaq tyfl acqurpy ndnrp
        asw ctiv mnxzyc weeuwb gsn bzk irbyhxl cgqomj izy zbk
        yrxcrbt bcrryxt pofe wwzl
    )";

    std::string input2 =
     R"(vuaqez kbtuyai vuaqez dxqud uvo gmhtg dxqud
        tpzs gqdxpxo zzpgta uurjx xpqxodg
        cil lsv vznqw vro zqzvjhm jhgauzw uxnwk lci zpgpu frjvyzo tsv
        zfvcuim gwn gnw dxfppok
        btb goof iwadca aac tbb jha uvzi
        qah ned ipmure kyta ffhrwe njz paq kaag xmlui
        rkmw vrblwyy gpax hxsf zpbza gypuwf jbib ypcjwd vrlybyw
        yfjljn uxpvg huik jsnah nkhsg yfjljn lqzsz
        hagjlqx agnax jqalxgh rvjgtc mjrmph azznzcq gxajlqh
        ipki bhoabp rmiyl dmjyxl zzsmap aju
        tyjrr rigrf ciq qic avmwu jtr wpq
        vuf cosgytm toycgms ufv qzpcbrs
        epzgxr lydrsj ezxrpg expzgr
        ecm prj kmak makk jpr
        ccwyq txy okj matxa socoa
        zrjphq gigayv ywkfmru yrwukmf fxjjrha gqkxx zhjy tisutx kufrywm izjfj igg
        lfhgsro gsroflh wrpo lofhgsr
        kgkgj wkhnab ubrjaoa ubrjaoa ubrjaoa ggdgh
        hztutpn epnqmz ffcroq mnqpez niibpn kdloak xjui ozttj lyzsc pzgq inpnib
        kruz sjqp mmd hhdxjgc mauouma asevvo upjwqi hxcgjhd etqzagp
        zylf qime cho oraid svytv gqrjufv mker cho vnkyiin tjms
        dotjul qyv hnh cibtg gdpauyx wzp
        fabtira ejxoeor cqyethv ndjrq hnxn joq otng lrr csytrub
        txhgepd fwdaanm nawdamf pxine qqrn pronw exnip qwkimt rvy
        kuxzhi jln urzxtw rzu ebsuylm tscru qwlhfgq nnu nuchvz vuht
        cqgu camlr umkltcf stx izp rtdwxff wkfvs
        jhje cxix lefcrsu nebv idfzhic xqri xkft
        utzxb znb ietupd uqgbhje aobip oawjwm hetyan uqtqv hpwzyri kwxyu
        jvzvbt xuyvp aegdkb srbw bzabpf lyfriez cruyfu
        nhi nih aeb ihn
        hcf zypt djcm pkjx pvhh
        rhvxcfk exydvk ids hybme hnk yfchvs mjbo meocn
        rpboxr rxoprb hdzje zhedj
        ziildbo apzvatr vsv isndq ebxyy ntm tdttg wkvdh qnids vkdhw xxolip
        ywu uyw ipcjz pjzci xjn kvgk vsocprw
        euzo njlpv ndrlhi drlnhi ivmjkb fjrtxta skvgmrd
        gbyvj dkck gevpfvb lhadhx rgjcdn yraxh bdk oen vqryd bkr
        vgkp hncttxb wgxh gdyjo bbdfzvc xhgw rznzgda yxrrlo gxhw
        ifjlb fpecyic svhjp ilmj oxgr svhaf
        vbqky lhccj xtmm xzjyykn oqmdq qywir bswly
        euxxziv totzer vsxfx leo djho uoeaz edaig fbu lumbi
        ooqtwq pvo kid vpo jxin bod btqc fbyuz
        jhabi mronu htqqyz umjcbv sgnbp wyn cetmt pcjf
        tnrkcyl dduuhxh rylkctn pwj rtynkcl mzzfomr
        rxx ldqffi ulappk nltawbn tplhb kyb cqyi
        vzkw gviooah vxh xeae ohvcad oaiwcj dkx
        sdofdjt hcifv dqws sia mlwm vfich kavh myzue roops mzuye
        uxs nlbmjp nlbmjp tlaxa tlaxa
        ynnisp twx xtw jgkc yinpns
        kumorsm wav xhx bpvz clqc ffmadzl ndny ymslo lobv
        ljzabj tqhves mezh pwn wue dwfqq lynvtt boeknvi xqbd pkud tzlanis
        lgq qiikzl oihnsr pivtjmu qhic yvmeebg rxu qgl yuxnqse dvu faxqez
        ldk mlwja vmdqr yzlxiua amlubt ejmzfx nonm zhkxbn gaqbnqq
        ttc ctt kneknx smtnaft abljip tct
        uybhbiw zwojzlm cfxoopp abulenj znz zzn opllzmm yufk witwxzp
        qvkybwi rdbxb qiuizmo fqgne jgot jxz dqhapn
        vzinf ehaley amnk laheye invfz
        pedakl ivld agzyhr wmzba tzzzg bazwm wjwgux thrnxkn
        cmyhae nwfs nfsw kmh pxkaffq
        vdf szupev tyunp qiiu deevxmy wozvtt nelnr kgdexy gparqj hajavz biizn
        pwspk skpwp ontbjee pkspw cfbj
        ihsmh djxtak wkzllao oyr djxtak prc
        uhvihqq jrgf hdfek pdrfpt tghz gthz awae wcygi wujti svq fhedk
        gnfhsj odqlt netmsul rviio nkzw nkzw
        xyvc clxw cyxv lxcw
        duegck pkviu npwsp zdx wpvn dmxgnv ixv fybs xteru
        vih kgk hads boaddu daiwo hozoufv nef vtcplc isiw
        tzqoo dqlgvno jzlay sywx ecej addt ecej addt mnfcu
        ymgmby zegudpx ipsjai ger wcwjw brzebb
        eqekxlx itra xekelxq exqkexl
        rciu ojaa ircu nxjga puvmwou remgu
        sltth pprimb slnxopq avtir hvpv ppww fhfap wisn kzs jcuuuuf
        xbppc ydpbq zhjh oym iljzvk vsb
        ueye shtps uccehi ccheiu dqm yeeu
        gwywf lcpv qza qza gzuovj jfzffyh oybfxqv
        aawi ynsvdco azdoz cqr tnyquq xlyvbx eca kcalpes
        zumgzhy rou kguqa vubw bwgd qprxcg etnbev nqmi
        fyd tuoz uwclqn cgl lrpkf irz dizv nxze clg jghx jbpt
        kwuanos eorjr tcahp kwuanos cyrpfji zxayggd kwuanos jkqt qqvbork lizk
        vtu ovje vhg ovje vtu zcy hrhtr puawfgv
        bliz exp wot svxv epx
        jiqgxwj yips hjsatc jgsrno msfp vxvbt bba bqmw xjgpgog
        vpvypp ggwp wggp gndp hedpse afji hcqgof
        hxueubt hiynoa qqzaj ohb qway
        akq nfnes sdrlza nfnes weq
        udxpdpx gctuv llhxuow rqtetm hdbnpte oebapv civy oeobu ftgivd pykj
        pbgbvn jgmr xrz dfn gosjobw ndf
        gnf dtbsnc fwcmml tscdnb fgn qgadusl eifpk
        vmnv yuxrup qcphi tanc tnca kjrv cphqi
        hclggs sghglc fgplp odn pfglp emkrulf whwtmbs qnuyg
        wcxtr ani ain sha hsa zxbkf bzxokat qezo ljqxi xqcwfmd dxo
        waiq smpbu dbyka uibxjrg nze wiqa rfpts ddjsjv jqqjez bpusm
        lpcxf vsbj owjwc tuqj vkrgrh jsjdepv oil lxrjox frsxsi clr
        vzunp prwk nnd rfs vpuzn
        pqpqv lvsk sqxf nhobsm hakbn ywj
        xxu uxx szqnmi lnwtmx
        akq nmlw fupwsth jduvhva
        nac wwlxqck hpbce vxxqa fyp xvxqa kxwclqw yvlmv bfwi
        pzxjbj nvwv mdooiez vvftp enjrsck iypu uhru fpx omtd
        llxgp qwf pwaj cuhb scloot hbcu jgp vjw ooclst
        sisd akawvzd wvdzkaa gyoij ikt eeeosb jiwiup
        tche vxj sbctqv jvx gosur usgor ibo yqxo qqgd zspl
        cidd welisl fxblxqk qxbklfx fbdoqcz glhq iylodvz zvds ghlq
        cnsa hrxst mrnkqtj bptq jmi cpbcofs kveyeur uzmga modphm rtx kntqjrm
        dvyup usfaq rtghoec bvcos fqsua zohwwg
        onf vncybi dlaxni oqyqqkn
        okfwa qyyx ebnv llql nphq etdt ytgivlo jwgwz kiob
        ann vqnqvpx wth lpwid bjvzw xpwqxcj azg ioeyzzp onwf
        smy epzomx xep yid zctvrfj astdj cfg fgc eriuxt
        rljqgin wzobzrh cuwtx vcsbx tmg tuysq vxipgho
        ewp rsrnsj wgeyin lrji ddgt utol xxwut fjiwopa
        upu ftvqbk tfkvbq fdwga rmu puu hbiasjw
        cfl lmqkb lfc wbtlfi uqsjs ejgmphi tbliwf nzcela gzb
        zop unwmiu acull mkwh hvruknw rfk mmhaz iqmenq fifino
        iczua bjut tlgf zicau jtbu
        mtka ipd mdifj kps
        irqkysw xfsjl tedx yckkbx iktxb sqxn pbfvubv uudzppz
        mdrn cihat wcext kufs awwtjok pfjg
        wdevt tyo zzbp pqlqq wdevt
        yhatqkv ntuhw tdfd buxazh xbcsv bas gkv rbzi tddf jbj bsa
        malip hiiy qezz yhii wlfojre
        zqnfll bssveq lprwbep bhqml tztbt
        npnxotu yupdytb jptqo klfydfe fpucmfq svxcqr unopxnt
        gdpz gwj iytiohu efk ctjzf asade abhotq brmhu tbtdur zzksbh
        kxft klzslf tjdzciy lzslkf
        ejei ezmemvg xlt zte tbwhz dgnfpao zotck wus uaz gbwbb
        dgednf vypmbs eiytot empfmny
        uopmui uehue wdvzt adpfcif mutl ifaztka vydi xumtz orstno
        dleero olxiq gxnlfm nfmxlg wloeavr olhrwg hrjd yicj ymyeex qav gxyjgfq
        hevj rqcne zycgb qgqtn rqcne ptfvu yyyu zlm hevj
        zrkhuh sttnkt hkuzhr vqtu
        ppsfm kcao qjq dgadglx cxaawjn pbucfu fed qgioarc dfe ricoaqg
        vmawf oktunea zraoir gkt zraoir jcvkqoq
        mqgml ecawug ugwace szwul iwbmooj owmiojb
        auggaw cypcuw npci vuyxijd pofswjx vdkrgx xylk rom ksj
        qmwx jgsrdj ikva xzxw avik
        zzhcqu rbg pywjdn wyndpj zchuqz
        wzd wqycftu yldezp zovuy oydia hovewe
        kfid qkkk thak qhbf rvzlzvu uuxh pbj hkat gow oeqcw knqqzha
        sua itv hfpg bdqye bznlrk hfpg bdqye kvir kaai ggtz jqn
        ulggl guitamm tkpckso fupacz otxtqpd jxnqc
        ueesb ndyik vjftz jgqqv nrcf
        krh dqpmsw fybzynl zhjbvkw exefc rhs neq ldprb bhhvxm pjwirun
        ymavl qwxr yavml wagwc ekokrpq zewppw iumcgin cxdvwx
        wwdukav kuawvwd kowv dkwvuwa
        eazot bil tzu vdwwbm fvauwrq
        esq tixokph yspf ztoxfut lgzush pwv swh pwv auqhuu tixokph
        pdbeyxi poio mugfkb brwbbx aao uszw fokjeb uswz
        sbs ryjr ptispi tvnhu htunv vthnu
        czjmg hbdjhvi jrkoy fpgwc syafy aar kvnq eaecsb wqzpx
        twtp dvl uvyje qtlzj dsvyr qpjnj eyoigx bhgpccy gwn dtuf
        mxit xunctu vbyks wmqc jriuupl ybvks uncutx nsoxwrb ykt prc
        yye mgf uhc irowpc dsdv iwaxod ftavlj dxzp tcch tcch mefz
        rxe xwrrgl xwrrgl duu rxe xbbgoe
        ucsz akswcd ojrmqq cox hgfh lxwu ltnnf cenikcp
        opjhdp svwezr svwezr opjhdp
        qojlkl ircxqnt utfmdg fcvr vehkcvt ufmzcpv xwlh ddavv xel bwlz fii
        rzkayeh iursm zhily hdnq fqydfvt uwoy hptpiqu tdqy bgr xdr
        ymruz umzry hbltwya jhwhzk flh tahylbw bdbaimb qscbp ntkuf
        uxpato owsqyao vaog oenomkc usrmnc epua vzkppls
        qxqczbk qyguz alawj xgjawtw wxtjgwa snfcdmz
        fjfgos rmpd mgs vbk dlls jkljao eoovdfb ucdvaoq qmjmqku ney porr
        nmcrqz zcoxpk dlnzksd ymh zyg spxss ruyk bychq gsgv eusiuid mnrqcz
        jbzadnx lzl sdamer okoico frqisrm lxet agriw
        xceoqr qai vahc jjzifsn exg
        igjpn wfy ukn aag quro wklsq cjq bgtjrdz gmub wyhh
        fzlwnm mygfn vkzwvw zvhsex gfki
        ijvzgai ebmeq wssfmbq uguh sfuutm nwkgmex dxael liakdxs rnf sky yowpxc
        bjzkyjh fced nji esowk qxsubsk qgtts
        nkdgo bbjfq fgnxnhd gfjchl jetdb xubsgj eiju ldlm oxsx znft bbqfj
        xovcnob pxfe pmstes yzkdm iqlvha nmcziix fexp ivqalh rxecqps
        xpyew xudfud wwqe qhfjlcu epv fnrbgyv ihli qngtx yjlfg ozqbzn esp
        timl gcohx vqzic gzm shwlkkv icqzv urchuc
        xpqq gaqzwo cci dowahsr gaqzwo
        jjsagdl umbpxre kyre zvaryft tmw pxpnjy
        aqovcz nunq nnuq xjrvvh autjmit jiatumt
        elg lps lge zjjot hwz tmqrup xaxxmo zlbzp uftd fukdad kvpymsm
        iokwzal ywti zbdmzbu lprywe wbgbwza ypogbga kzliwao wstqi eqm keaeaj gbabwwz
        lwfpk mhufe eddzgd ljxyqy vhzkct uemhf
        lwqil fzugdo faq feppo usl llwqi
        nje hthr ropq qvcepu bexszfj avmzjvv zajmvvv fhcd xnc cnx qnuaux
        kvksn dphbyz nsx wrcc ccrw
        nzpa pzzunfv ygzjy gxrrtcj hrt trh pwxpg yifgjmo fnupzzv wbzx
        aepti rbojui ypvhe ubojri tcema aan dntkw qjx bfvmyos tcm hvoqytn
        qpwq exu jvsiwj gsw avr vbemldy
        xsbzpf xbzyvx xax sxh vpxt gccy xxa zhgbwoa hwwxoky fhvdxfc pvtx
        pnsa ovtjolz tyutl eyjjzt jvtoolz owbypvr tytlu ewtzgec
        cyg dwwk eihsp aeuk bbnay aluwyz hdmv uaek mwt ihpse wjhnkeg
        fhzx vjetz vjub tejvz
        ewwyb jidhu pyvyenn igtnyd tiwr akwkkbi myz xxjwb jjrdeg
        jbkuw kwir rkiw ubwkj
        bltffuw lftwufb hhsh wfbtulf nrxaa rlszi toijxnz czlci
        bqrm pga zgblgcw pgwhhn lcgzwbg bcgzlgw yqb
        mhjj vjoa gnjlc kclcr ito ofksy giavy fpqeioj
        bkiqmif izidbui sttxxi bswhkxp sduuw
        mjgnvw mjgwnv ojzyuv gvj
        qxn kkhc whd fgwk auzugg augzgu kqfov wfgk
        spdxbnu xpfofsb bpfsoxf ahjywql spbxoff
        bwqxhlm wbqlxmh kqgpl fyzgf guhkvgx ovk qhmp gnrmu wvd wedj
        vvwf hcnc vvwsngj qedzoxm hcnc qedzoxm kjthdi cbwqep qtvu
        gio iqklmro noqablo bab jiqc rwebyg rqkloim wzmgs uunl amqs iwj
        snxj szobqt zcgvwv wiyqknu
        uto jteikwd cew gqsks hmvjtcy sach
        zpgl qnkoex amhufmr figns upv xezrl rjleak nwrna
        pzkvrdz dtonazj gtr gfxucuf lstjl lsjtl rgkope kzpdzrv lyptn zfxjys ttk
        ddxgm lumlgki jhv doft kok swy ckds swy ddxgm lbfbdv
        qfs rcufzgz iaiqw qfs qfs
        nvkbo sgv mquwb ritpye nbkov poex hraorm qrrr qdt qefl
        irxannd fiud ehyb ggx plqg pvvn uuptop tcvbm abuf bcfnmw
        qwya ukblz epmbfr vmlon yqwa
        hlo mmv vmm mvm
        svzpxun yugbbe sbbpxs dmy xspbbs zhpovyf fyovhzp cpbt pke
        zgk gft zybs zrgcoo ypu bue htgo
        xnesq srsx pkzaoh cfqzugh
        lntd nvxetbv clykjpd svmibpx evxtvnb yldkpjc
        jsqq tzwak hephg eqwczd ioisa yim tmdifn mceip
        kuwqz wzkqu zwchmj lfec uexne iztp llityt
        kvamkpc pvbryqh ion cwizjde gln kcpvmak pzzlw gnl
        ydeqf bfaab sydqhbp smsxdjr pynrs cqymt
        onb eiab bno nob
        mqslq scnelxv hyllrf scnelxv mqslq wmnbk
        pttu kubby lgop bbyuk gsk skg ikktlbb inbyvz
        xznvl zwtdj vbxdyd clhw
        hgy zudelp ickc drfjgn iyws xhc
        zzv wik iorhat qkb kjb lykdz vrce yjsjwj
        gyw xzgbi efus uuy
        hwcy ujdun bjjuvd jbdvju onnk xeyy mmp onkn qyzl
        jwfm ptjwrbl hhuv uolz adyweh qpj wxyogp igvnojq jmfw pqs fsnirby)";


        Day4_1(input1 + input2);
        Day4_2(input1 + input2);
}

int main()
{
    //Day1();
	//Day2();
   // Day3();
    Day4(); 

    return 0;
}

