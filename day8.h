#pragma once


enum class Operator { Inc, Dec, L, LE, G, GE, E, NE };

struct Instruction
{
    std::string registerName;
    Operator operation;
    int value;

    struct Condition
    {
        std::string registerName;
        Operator operation;
        int value;
    }
    condition;
};

typedef std::vector<Instruction> ProgramType;
typedef std::map<std::string, int> RegistersType;

Operator ParseOp(const std::string opString)
{
    if (opString == "<")
        return Operator::L;
    else if (opString == "<=")
        return Operator::LE;
    else if (opString == ">")
        return Operator::G;
    else if (opString == ">=")
        return Operator::GE;
    else if (opString == "==")
        return Operator::E;
    else if (opString == "!=")
        return Operator::NE;
    else if (opString == "inc")
        return Operator::Inc;
    else if (opString == "dec")
        return Operator::Dec;
    else
        assert(0);
}

ProgramType ParseProgram(const std::string& input)
{
    ProgramType program;

    std::stringstream inputStream(input);
    for (std::string line; std::getline(inputStream, line);)
    {
        char regName[256];
        char op[256];
        int value;
        char condRegName[256];
        char condOp[256];
        int condValue;

        int itemsParsed = sscanf(line.c_str(), "%s %s %d if %s %s %d", regName, op, &value, condRegName, condOp, &condValue);
        assert(itemsParsed == 6);

        Instruction instruction;
        instruction.registerName = regName;
        instruction.operation = ParseOp(op);
        instruction.value = value;
        instruction.condition.registerName = condRegName;
        instruction.condition.operation = ParseOp(condOp);
        instruction.condition.value = condValue;

        program.push_back(instruction);
    }

    return program;
}


int RunProgram(RegistersType& registers, const ProgramType& program)
{
    int largestValue = 0;

    for (const Instruction& instruction : program)
    {
        bool conditionPass = false;

        switch (instruction.condition.operation)
        {
        case Operator::L:
            conditionPass = (registers[instruction.condition.registerName] < instruction.condition.value);
            break;
        case Operator::LE:
            conditionPass = (registers[instruction.condition.registerName] <= instruction.condition.value);
            break;
        case Operator::G:
            conditionPass = (registers[instruction.condition.registerName] > instruction.condition.value);
            break;
        case Operator::GE:
            conditionPass = (registers[instruction.condition.registerName] >= instruction.condition.value);
            break;
        case Operator::E:
            conditionPass = (registers[instruction.condition.registerName] == instruction.condition.value);
            break;
        case Operator::NE:
            conditionPass = (registers[instruction.condition.registerName] != instruction.condition.value);
            break;
        default:
            assert(0);
        }

        if (conditionPass)
        {
            switch (instruction.operation)
            {
            case Operator::Inc:
                registers[instruction.registerName] += instruction.value;
                largestValue = max(largestValue, registers[instruction.registerName]);
                break;
            case Operator::Dec:
                registers[instruction.registerName] -= instruction.value;
                largestValue = max(largestValue, registers[instruction.registerName]);
                break;
            default:
                assert(0);
            }
        }
    }

    return largestValue;
}


void Day8_1(const std::string& task, const std::string& input)
{
    ProgramType program = ParseProgram(input);

    RegistersType registers;
    int largestValue = RunProgram(registers, program);

    int largestValueCurrentState = INT_MIN;

    for (auto& kv : registers)
    {
        largestValueCurrentState = max(largestValueCurrentState, kv.second);
    }

    PrintDbg("Day8_1 %s: %d %d\n", task.c_str(), largestValueCurrentState, largestValue);
}

void Day8()
{
    std::string sample =
        R"(b inc 5 if a > 1
           a inc 1 if b < 5
           c dec -10 if a >= 1
           c inc -20 if c == 10)";
    Day8_1("sample", sample);


    std::string input1 =
        R"(js inc 257 if wn < 9
jq dec -586 if esb != -3
gcf inc -603 if i >= -9
gcf dec -300 if d != 1
g inc -973 if gy > -1
epp dec -79 if rjx < 9
x dec 796 if esb == 0
d inc -526 if rf < 3
qc inc -610 if dma > -8
gcf dec 831 if aqr > 5
wow dec -705 if jq >= 583
gcf dec 135 if esb < 10
gcf inc -777 if aqr != 8
esb inc 262 if rjx > -10
x inc 259 if dma > 3
g dec -784 if rjx != -2
rjx inc -969 if yzp > -3
wow inc -401 if g < -182
dma inc 995 if rjx <= -962
vyy inc 290 if g >= -194
vyy inc 4 if gy == 0
vyy dec -295 if wow >= 314
j dec 476 if j >= -8
u inc 84 if g < -195
g inc -422 if gy == -4
yzp dec -523 if cty == 0
cn dec -938 if g > -195
u dec -652 if g <= -193
aqr dec 829 if qc < -601
u dec 199 if wow < 309
aqr dec -409 if rf >= 9
dma dec -556 if dma > 990
qc inc 134 if i != 0
qc inc 238 if j >= -476
yzp dec 810 if js < 255
i dec 898 if i == 0
g inc 898 if tyg <= -5
j dec -130 if aqr == -832
tyg inc -504 if l > -7
aqr dec 465 if l >= -9
gcf dec 64 if jq != 595
wow inc -102 if yzp >= 515
rf inc -433 if i == -898
rjx inc -334 if l >= -6
rf inc -395 if cn <= 947
u inc -724 if qc < -376
epp inc 309 if gcf >= -1281
zp dec -367 if cty >= -5
aqr dec 265 if aqr <= -1287
u inc 359 if wn == 0
vyy inc 587 if aqr != -1550
uxa inc -541 if u <= 162
js inc 720 if wow >= 195
d inc -857 if wn > -3
cty inc 958 if gcf == -1279
rf dec 153 if x >= -804
cn dec -921 if dma <= 1560
zp inc -554 if qc > -381
jq dec 83 if x < -799
qc dec 912 if cty < 968
i inc -636 if tyg == -504
rjx dec 113 if aqr >= -1566
js inc -184 if wow > 198
qc inc -519 if cty != 958
aqr dec 281 if u > 166
aqr inc 392 if vyy <= 887
cn inc -179 if rjx > -1420
g inc -16 if cn != 1680
d inc 260 if uxa != -541
j inc -873 if yzp < 522
rjx inc 737 if g >= -191
wow inc 288 if qc >= -1287
j inc -844 if wn > 5
i inc 91 if uxa > -546
yzp inc -12 if d == -1383
cn dec -247 if zp >= -189
i dec -246 if dma == 1551
qc inc -919 if gy >= -3
cn dec -804 if esb < 270
uxa inc 593 if qc != -2197
yzp inc -562 if esb <= 264
rjx inc 850 if zp < -181
u dec 944 if j != -486
vyy inc 970 if vyy >= 881
gy inc 659 if u < -779
aqr dec 145 if esb == 262
yzp inc 346 if gcf == -1282
wow inc 112 if gcf != -1279
vyy inc -120 if rjx == 171
esb dec -795 if qc >= -2210
cty inc -282 if zp == -187
uxa dec -683 if l == 0
epp inc -185 if jq >= 589
js inc 542 if cn != 2741
gy inc 591 if d == -1383
wow inc -734 if rf != -987
wow dec 482 if vyy <= 1739
uxa dec 231 if u >= -785
gy dec -153 if d != -1385
dma inc 682 if js > 1330
wn dec -173 if i < -1196
tyg dec -510 if dma > 2230
aqr inc 309 if gcf <= -1289
gcf inc 831 if g > -190
g dec -457 if qc == -2203
aqr dec -682 if gcf != -447
cn dec 75 if js > 1328
vyy inc -639 if cn >= 2666
j dec 119 if uxa != 499
i inc -312 if gy > 1399
rjx dec 145 if aqr != -634
cty dec -600 if wow == -726
dma inc 79 if zp < -179
vyy inc 285 if jq <= 586
tyg inc 34 if d < -1379
u dec -320 if yzp != -44
esb inc -229 if wow >= -730
gy dec 175 if cn != 2659
gy inc 87 if js <= 1334
wn dec 725 if rjx < 35
cty dec -64 if gy == 1228
tyg inc 809 if gcf != -438
zp dec -526 if uxa > 500
rjx inc -520 if wow > -727
gy inc 608 if cty > 1345
u inc -847 if cn == 2656
dma inc -728 if zp < 343
qc dec -722 if wow > -734
gy inc -864 if wn != -552
l dec -53 if cn == 2656
rjx dec -674 if gcf > -446
i dec 647 if jq == 586
dma inc -109 if cty <= 1349
d dec -263 if j == -595
rf dec 835 if rf < -972
esb inc 504 if js >= 1332
uxa dec -215 if wow > -732
l dec 240 if qc != -1472
tyg inc 754 if aqr > -639
d dec -784 if d > -1129
u dec 528 if dma == 1482
x dec 569 if aqr != -636
uxa dec -163 if yzp < -49
qc inc -88 if x != -1365
gy inc -966 if yzp <= -43
cn inc 870 if gy == 262
x dec -511 if gy > 263
qc dec -245 if epp >= 380
rf dec -718 if vyy >= 2018
aqr inc 494 if u != -1302
esb dec 211 if wow < -734
esb dec -284 if epp > 379
x inc 354 if x >= -1372
g dec 378 if cty != 1349
wow dec -405 if js < 1338
tyg dec 615 if yzp != -51
rf inc 475 if dma == 1475
gy dec 15 if aqr <= -132
zp inc 915 if zp != 335
d dec 323 if wn >= -553
g dec -525 if cn != 3517
l dec -13 if gy <= 248
gy dec -687 if i != -2147
tyg inc -487 if gy == 934
rjx dec 444 if vyy == 2014
wn inc 449 if yzp < -46
cn inc 651 if rf != -1337
zp dec 888 if jq >= 578
uxa dec 966 if esb > 1616
wn dec -219 if tyg != 1109
dma inc 599 if cn > 4176
x inc -486 if epp >= 387
l inc -404 if yzp != -43
rjx dec -996 if aqr > -142
g dec 215 if dma == 2079
aqr dec -746 if i > -2159
gcf dec -301 if cn >= 4174
qc inc -700 if vyy == 2016
rjx dec 289 if d >= -661
vyy inc 278 if gcf < -138
g inc 659 if wn != 118
zp inc 622 if l <= -579
zp inc 644 if zp >= 373
aqr inc 468 if gy >= 931
wn inc 608 if zp > 359
js dec 985 if gy <= 942
uxa dec 509 if epp > 383
tyg inc 134 if cty <= 1340
jq dec 677 if dma < 2073
yzp dec -146 if j >= -600
l inc -500 if dma == 2072
cn inc 399 if cty <= 1341
rf inc 521 if wow != -321
gcf dec -70 if wn > 718
gcf dec 946 if tyg == 1250
cty dec 398 if qc == -1936
qc dec -105 if qc > -1936
g dec -16 if g != 1082
cty dec 932 if vyy > 2288
gcf dec -293 if esb != 1616
cn dec 244 if esb >= 1610
rf inc -790 if cn != 4338
dma dec -87 if wn == 724
cn dec -191 if j > -598
aqr inc -246 if d <= -658
cn inc 786 if vyy <= 2297
g dec 211 if qc < -1932
x inc -473 if l >= -587
rjx inc -686 if jq <= 589
dma inc -411 if gcf <= -1019
u inc -596 if qc <= -1933
l inc -60 if rjx > -476
wow dec 910 if zp == 366
gy inc -854 if u != -1916
jq inc -698 if wn <= 729
zp inc 456 if d != -665
x dec -853 if x >= -1964
aqr inc -282 if rjx < -478
tyg inc 975 if cty == 10
js inc -684 if wow >= -1239
uxa dec 702 if g == 879
g inc -602 if tyg <= 2231
cty inc 987 if dma > 1742
gy dec -57 if cn == 5317
zp dec -527 if qc > -1941
tyg dec 689 if g != 282
gcf inc -11 if rjx > -478
epp dec 44 if uxa < -325
aqr dec 936 if i < -2156
i dec -119 if aqr >= 841
yzp dec 46 if uxa > -330
u inc 549 if esb == 1619
zp dec 412 if j >= -598
cn dec -865 if gy < 89
yzp dec 366 if g > 283
j dec 372 if j <= -595
zp inc 879 if tyg > 1532
wow dec 30 if x > -1974
dma dec 288 if j < -966
zp inc -419 if epp == 344
tyg inc 304 if x < -1964
zp dec 77 if j < -960
cty inc -586 if wn < 728
wow inc 271 if wow == -1261
u inc -751 if dma != 1470
wow dec -64 if wn != 727
esb inc 294 if gy <= 75
jq inc -559 if wow > -918
cty inc -283 if gy != 73
cty dec 792 if g != 274
l inc 589 if rjx >= -482
gy inc -659 if jq < -116
cn dec -817 if aqr <= 839
l inc 682 if rjx < -467
l dec -285 if rf <= -2125
qc inc -370 if x < -1961
l dec 582 if yzp >= 47
dma inc -365 if js == -334
js inc 397 if d == -659
g inc 902 if aqr <= 840
x inc 129 if rf >= -2139
g dec -704 if gcf < -1041
cn inc 207 if uxa > -332
epp dec 517 if js < 70
cn dec 125 if qc <= -2305
x inc -187 if tyg > 1844
gy dec -1 if cty < -661
js inc -224 if qc != -2306
x inc -627 if gcf <= -1025
yzp inc -426 if g < 1186
uxa dec -839 if wow >= -933
u inc 688 if gy <= 87
jq dec -453 if aqr < 834
tyg inc -370 if d >= -660
l dec 81 if gy != 89
zp dec -184 if uxa == 510
gcf dec -97 if gcf == -1034
tyg inc -508 if x != -2468
cty inc 89 if j < -960
jq dec 416 if rf >= -2132
rf inc -846 if cty >= -577
uxa dec -315 if vyy <= 2294
g inc -191 if vyy == 2294
js dec -557 if wow == -934
u dec 382 if qc >= -2313
dma dec -841 if wow > -929
u dec 6 if dma < 1932
aqr inc 75 if js == 63
jq inc 640 if gcf < -928
wn inc -992 if j != -967
uxa dec -577 if wn != 726
g inc -458 if rjx < -467
epp dec 141 if x == -2468
l inc 617 if cty < -576
gy dec 542 if yzp != -377
cty dec -99 if uxa < 1410
tyg inc -358 if g > 521
wn dec 514 if uxa <= 1401
dma inc 110 if j > -960
js inc -359 if jq <= 569
epp dec 266 if epp < -312
x inc -473 if jq > 557
vyy inc 890 if wn == 730
zp dec 379 if gcf != -932
u dec 46 if jq == 565
tyg inc -410 if l != 256
i inc -320 if js != -303
l dec 670 if i >= -2482
i inc 788 if u < -2391
l inc 23 if cty == -476
tyg inc -364 if rf <= -2969
gy dec 394 if epp >= -584
esb dec 645 if aqr != 907
epp inc -842 if x < -2935
js dec -289 if l == -392
tyg inc -405 if gcf == -937
vyy dec -58 if epp == -1419
gy dec 110 if u == -2398
vyy dec -789 if epp > -1426
qc dec 463 if zp >= 1117
gcf inc 859 if esb == 1616
u inc -99 if js < 2
epp inc 111 if tyg == -67
jq inc -536 if d < -661
js inc 506 if dma <= 1936
rjx dec -58 if j >= -971
wn dec -513 if tyg <= -64
wow dec 816 if aqr >= 902
gcf inc -957 if x == -2941
uxa dec -39 if yzp <= -377
wn inc 824 if g <= 531
gcf dec 927 if l >= -394
x dec -655 if l == -392
g inc 767 if tyg > -59
dma inc -493 if epp != -1318
esb inc -587 if epp >= -1318
wow inc 996 if cty >= -479
l dec 119 if epp != -1311
gy dec -935 if uxa < 1444
gcf dec -428 if zp >= 1121
js inc -999 if x > -2293
uxa dec 438 if epp != -1305
gcf dec -623 if yzp <= -380
j inc -256 if gcf < -1530
l inc -183 if d >= -662
wn dec 945 if x < -2279
i inc 953 if epp == -1311
vyy inc -434 if js > -1016
yzp dec -695 if epp < -1308
d inc 975 if l == -575
uxa dec -218 if j < -1216
gcf inc 413 if tyg == -67
wow inc -380 if zp != 1125
cn dec 166 if wn > 1113
rjx dec 878 if l != -581
esb inc -745 if g <= 531
aqr dec 14 if esb < 292
j inc 405 if jq == 565
vyy inc 657 if wn == 1124
j dec -624 if qc > -2763
rf inc -711 if esb < 289
uxa inc 453 if gy >= 512
i inc 593 if js >= -1009
qc inc -413 if j > -826
tyg inc -395 if epp == -1311
cty dec -911 if g >= 524
yzp inc -259 if esb >= 277
dma dec -812 if vyy > 2643
wow inc 887 if gcf >= -1121
uxa inc 906 if rf < -3686
l inc -816 if js > -1002
aqr inc -123 if tyg >= -462
x inc 413 if uxa < 2590
tyg dec -141 if wow <= 142
cn inc -138 if gcf > -1118
i inc 665 if wn < 1117
wow inc -250 if gy > 505
wow inc 751 if l != -569
j inc 334 if x >= -1879
i inc -963 if uxa >= 2575
uxa dec -395 if wn == 1106
dma dec 130 if esb != 290
l inc 171 if zp > 1122
esb inc 288 if uxa < 2576
wn inc -672 if i > -445
uxa inc -593 if jq == 565
cty inc -247 if yzp >= 52
vyy inc 480 if cn == 6907
js dec -402 if uxa <= 1982
l dec -121 if cn < 6913
rjx dec 692 if i <= -433
g inc 827 if cty >= 186
d inc -333 if i >= -449
zp inc 438 if u > -2502
gy dec -418 if cn >= 6902
x dec 665 if uxa != 1980
zp dec 497 if l == -283
i inc -51 if rf >= -3694
dma dec -792 if gy < 931
dma dec -189 if wn <= 435
cty dec 337 if g != 1347
zp inc -436 if dma == 2919
yzp dec -184 if rjx <= -1980
gcf inc 688 if qc <= -3174
u inc -536 if zp <= 636
d dec 31 if rjx != -1989
esb dec 523 if wow >= 651
gy inc 566 if zp >= 632
vyy dec 190 if zp == 630
tyg inc 53 if i < -486
x dec -543 if i < -482
uxa dec 403 if epp != -1319
i inc 880 if u == -3033
wn dec 172 if gcf < -428
qc dec 316 if cn > 6904
gcf dec 864 if rf == -3688
esb inc -344 if uxa <= 1583
i inc -234 if js >= -1006
x dec -306 if d < -45
vyy inc -256 if rjx >= -1983
u dec -498 if epp > -1309
esb inc -915 if u == -3033
i inc 910 if esb < -624
l dec 781 if qc > -3505
g dec 803 if u < -3032
dma dec 392 if u == -3033
cty inc 216 if vyy != 2929
zp dec 12 if gy == 930
gy dec -35 if tyg >= -269
wow inc 824 if wow != 642
js inc 974 if epp >= -1319
gcf inc 883 if dma != 2527
jq inc 339 if cty != 72
yzp dec 751 if zp != 627
tyg inc 90 if x < -1679
vyy inc -212 if rjx < -1976
wow dec -642 if epp <= -1302
d dec -643 if x <= -1689
i dec -25 if vyy != 2728
js inc -522 if tyg == -178
js dec -880 if epp == -1311
l inc -899 if x == -1689
u dec 459 if g < 563
tyg dec -485 if i > 1083
zp dec -944 if dma < 2537
cn inc 867 if cty > 57
i dec -95 if jq == 904
gcf dec 548 if d == 595
gcf inc 35 if aqr >= 766
x inc -420 if yzp != -501
x inc -308 if yzp == -500
vyy inc -407 if l <= -1961
gy inc -623 if j < -476
u inc -932 if g > 547
zp dec 18 if js > 324
g dec 776 if cn > 7771
jq dec 581 if cn == 7764
zp inc 392 if g < -215
vyy inc -266 if i < 1185
tyg inc 600 if jq < 906
wow dec 480 if aqr != 770
yzp dec -97 if j <= -488
cn dec 212 if wow == 1284
vyy dec -247 if rjx == -1992
x dec -13 if uxa != 1584
wow inc 929 if vyy < 2330
qc inc 515 if vyy != 2313
wow dec -484 if u <= -4424
wn dec -251 if wow > 2699
dma inc 128 if d > 585
epp inc -429 if cn > 7564
tyg inc 401 if gy < 344
)";

std::string input2 =
        R"(dma inc -757 if qc == -2975
rjx inc 124 if tyg == 1308
j dec -258 if wn < 279
zp inc 265 if u != -4431
epp dec -850 if epp <= -1308
jq inc 875 if cty > 64
esb dec -585 if yzp <= -509
qc inc -663 if vyy != 2313
cn dec 194 if rf < -3682
i inc -821 if rjx > -1862
qc dec -768 if i != 354
rf inc 949 if gcf != -1805
wow inc -350 if gcf == -1807
l dec -72 if dma <= 2663
qc inc -201 if x <= -2106
cty dec -576 if esb == -631
uxa dec 387 if i >= 358
uxa inc 189 if uxa >= 1193
i dec 193 if qc > -3089
gcf inc -164 if wow == 2697
aqr inc -154 if cn < 7364
dma inc 145 if j < -228
cn inc -314 if rf > -2749
qc dec 976 if yzp > -509
tyg dec -277 if j == -226
l dec -339 if yzp < -501
qc dec -615 if js > 320
x inc -678 if rf >= -2743
rjx inc -777 if g > -228
rf dec 151 if vyy <= 2320
js dec 591 if u <= -4422
i inc 166 if d != 585
cn inc -615 if esb < -634
qc dec -148 if dma > 2649
gy dec -93 if d == 595
esb dec 265 if js < -256
wn inc 784 if x != -2795
rf inc 123 if yzp < -499
tyg inc 51 if rf <= -2777
dma inc 273 if tyg != 1575
g dec 546 if uxa == 1386
j inc 787 if l < -1546
rf inc 97 if qc <= -3289
x inc 621 if uxa <= 1388
cn inc -760 if esb <= -894
jq inc -89 if zp <= 2197
uxa dec -485 if wow == 2697
j inc 971 if rjx == -2638
rjx inc 117 if l != -1552
yzp inc -335 if wn < 1059
gy dec -871 if j <= 1541
tyg dec -602 if yzp != -852
rjx dec -852 if cn > 6293
g dec 893 if cn > 6293
uxa inc -524 if cn > 6297
yzp inc 389 if i < 347
epp dec -502 if rf > -2667
dma dec 323 if yzp > -453
l inc -921 if wow <= 2706
yzp dec -534 if jq > 1777
yzp dec 94 if rjx != -1784
uxa inc 254 if vyy != 2320
i dec 224 if gy <= 1313
u inc -466 if vyy < 2318
epp dec -751 if cn <= 6299
qc dec -316 if tyg >= 2197
d inc -666 if epp == 290
g dec -398 if js != -274
rf dec 482 if cn == 6304
vyy inc 295 if cty == 643
wn dec -540 if i != 108
qc inc -334 if wow != 2691
d dec 315 if dma < 2935
qc dec -860 if d != -385
qc dec -202 if gy > 1296
wow dec -67 if vyy > 2610
esb dec 880 if vyy != 2621
cn inc -985 if d <= -383
epp inc -435 if g == -1263
gcf dec 559 if u != -4419
aqr dec 979 if yzp >= -23
jq inc 905 if wn < 1597
cn inc -679 if x >= -2165
rf inc -590 if j != 1532
l dec -73 if wn <= 1598
qc dec 804 if d > -388
j inc 42 if zp < 2198
tyg dec -636 if qc < -3366
gy inc 209 if vyy != 2613
l inc -725 if x < -2158
qc inc -54 if j >= 1531
cty inc 896 if js < -258
u dec -718 if d <= -377
l dec 654 if esb >= -1785
dma dec 912 if i <= 120
uxa inc 827 if cty <= 1543
rf dec -871 if g >= -1271
uxa inc -77 if tyg > 2814
d inc -59 if i <= 121
dma dec 792 if cn == 5309
zp inc 930 if yzp >= -15
gy inc -956 if d == -435
wn dec -205 if j <= 1540
d dec -830 if cty >= 1536
tyg inc -552 if u != -3700
rf inc -616 if gcf != -2533
yzp dec -87 if rf >= -1793
uxa inc -886 if dma <= 1226
g inc 278 if uxa < 1741
j dec 1 if vyy > 2614
d dec 899 if rjx == -1786
rjx dec 238 if vyy >= 2606
cn inc -663 if d <= -505
rjx inc -805 if l != -3785
tyg dec 610 if aqr != -206
gcf inc 842 if yzp <= -12
tyg dec 361 if l <= -3772
wow inc 717 if dma != 1219
vyy dec 182 if gcf != -1695
l inc -972 if vyy >= 2428
cn dec -106 if gy <= 1517
g dec 598 if cn >= 4749
l dec 653 if rf <= -1808
epp dec -768 if esb != -1781
rf dec -566 if uxa != 1740
aqr inc 639 if cn == 4752
wn inc -877 if u == -3699
uxa dec -7 if vyy >= 2427
yzp dec -107 if qc != -3430
yzp inc -426 if esb <= -1776
epp inc 102 if x < -2164
u dec 396 if jq == 2684
dma dec -6 if jq <= 2686
cn inc -739 if gcf > -1698
gcf inc 470 if cty == 1539
gy inc 781 if vyy != 2433
vyy dec 238 if dma < 1236
wow inc 670 if wn != 1801
i dec -230 if jq < 2686
wn dec -500 if wow == 3481
wow dec 865 if j < 1536
x inc -733 if jq == 2684
cty dec 531 if gy >= 1513
g inc 399 if esb < -1768
x inc 201 if rf == -1233
cn inc 394 if d < -515
epp inc -953 if wow >= 2615
qc inc -639 if u != -4095
i inc 935 if vyy > 2191
g inc 846 if gcf != -1218
epp dec 89 if yzp > -334
qc dec -143 if epp >= -317
gy dec 256 if zp != 3132
tyg inc 545 if rjx > -2831
cn dec 913 if gcf != -1226
esb inc -410 if d == -514
rjx dec -71 if tyg <= 1849
rjx inc -127 if yzp > -336
jq inc -206 if gcf >= -1221
i dec -800 if gcf > -1225
aqr inc 98 if gy < 1263
gcf dec 163 if gcf <= -1213
cty dec -965 if zp == 3131
rjx dec -969 if cty < 1976
uxa inc 51 if x == -2698
u dec -380 if wow == 2616
tyg dec -715 if rjx >= -1922
zp inc -825 if yzp >= -323
zp dec 292 if x > -2702
esb inc -415 if d <= -505
wn inc -240 if esb > -2609
gy inc 882 if rf == -1233
vyy dec -638 if gcf <= -1384
tyg dec -63 if jq <= 2479
dma inc -38 if uxa < 1797
qc inc 289 if wow < 2619
d inc 342 if yzp >= -330
cty inc 650 if js < -271
l inc -129 if esb == -2601
jq inc 453 if j > 1531
esb dec 11 if i > 2084
wow inc -729 if wow < 2620
x inc 132 if uxa <= 1796
l dec 818 if vyy <= 2832
tyg dec 804 if yzp != -334
wow inc 285 if rf != -1233
zp dec -329 if wn != 2061
u inc 720 if js == -265
gcf inc 85 if aqr != 528
wow dec -303 if jq != 2472
vyy inc -366 if cty < 1965
yzp inc 598 if cty == 1973
rf inc 685 if jq >= 2471
vyy inc -385 if jq <= 2487
aqr inc 103 if esb >= -2598
d inc 427 if uxa == 1793
rjx inc -736 if zp < 2849
x dec -991 if esb <= -2600
gy inc 642 if gcf <= -1391
yzp dec -726 if wow < 2195
zp dec -582 if u == -3002
rf dec -354 if cn > 3093
g inc -150 if g != -342
uxa inc -381 if wn >= 2060
wow inc -145 if qc < -3628
g inc 589 if qc <= -3626
jq dec -643 if js == -265
yzp dec -768 if cty == 1973
vyy dec 448 if aqr <= 533
uxa dec 507 if cn <= 3103
gy dec 134 if aqr >= 521
x dec 868 if rf != -194
gcf inc 355 if cn >= 3093
rf dec 639 if tyg == 1822
gcf inc -671 if wow >= 2048
jq inc 615 if gy != 2012
zp dec -910 if cn < 3096
rjx inc 949 if wow < 2055
esb dec 623 if jq != 3731
g dec -799 if qc != -3634
uxa inc -352 if rf >= -196
gcf dec 229 if jq != 3729
zp inc 785 if rf > -200
i dec 150 if gcf < -1251
gcf inc -463 if dma != 1189
j inc -424 if wn == 2061
l inc 412 if gcf <= -1715
aqr inc -646 if u <= -2994
i inc 195 if l <= -4471
rjx inc 291 if cty < 1982
epp dec 459 if dma != 1198
u inc -909 if vyy > 1998
uxa dec -208 if vyy > 1994
u dec 727 if i == 1928
x inc -402 if l == -4468
u inc -459 if cn > 3095
j inc 253 if jq < 3733
vyy dec -143 if rf > -204
rjx dec -560 if tyg < 1822
cn dec -602 if jq > 3732
wow dec -231 if wn >= 2066
js inc -40 if x > -1972
gcf dec 591 if rjx >= -842
wn inc -612 if u <= -5090
vyy inc 60 if j >= 1100
cty dec -207 if tyg == 1819
wow dec -862 if dma < 1197
cn dec 534 if i <= 1936
d dec 380 if wow == 2907
x inc 48 if dma < 1199
yzp inc 955 if dma != 1191
dma inc -372 if l <= -4467
uxa dec 83 if wow != 2909
u dec 383 if u > -5102
cn dec 691 if cn <= 3169
vyy inc 952 if jq == 3733
j dec -231 if wn < 1444
i dec -988 if x >= -1931
cn dec -459 if x > -1936
js inc -714 if epp != -779
gy dec 751 if cn <= 2936
epp inc -45 if vyy != 2203
aqr dec -251 if i != 2916
zp dec -248 if x == -1929
vyy dec -917 if tyg > 1814
l inc 906 if rjx > -855
wn dec -262 if aqr >= -120
js inc -293 if j >= 1108
g inc -507 if uxa < 671
tyg dec 848 if uxa < 680
tyg inc 449 if cn != 2931
jq inc 43 if d >= -474
uxa dec 510 if rjx != -852
u dec -15 if cn <= 2936
rf dec 467 if uxa < 688
dma dec 40 if j < 1114
cn inc 256 if l > -3564
uxa dec -193 if cty <= 2173
cn inc 472 if epp <= -773
g dec 509 if qc != -3621
x dec -909 if wow >= 2902
j inc 809 if rf > -663
epp inc 458 if x > -1028
cty dec -210 if wn > 1707
wn dec 778 if rjx <= -848
zp inc 745 if l == -3570
dma inc -86 if rjx != -852
dma inc -964 if aqr > -126
x inc -741 if wow == 2909
cn inc -751 if esb <= -3217
cty dec 910 if qc >= -3636
gcf inc 496 if epp >= -321
rf dec -516 if epp >= -322
dma inc -112 if dma <= -187
yzp dec -376 if zp >= 4451
js dec -829 if qc >= -3629
rf inc -310 if dma > -188
gy inc -312 if wow >= 2899
cn dec 889 if dma > -186
g inc 667 if uxa > 682
u inc 201 if u != -5462
cty dec 589 if yzp > 3082
gy inc -274 if wow != 2907
u dec -533 if tyg == 1420
zp inc 937 if d >= -469
jq dec 18 if cn == 2024
cn dec -59 if rjx <= -850
dma dec -172 if x > -1026
jq dec 129 if gcf > -1231
wn dec 957 if jq < 3627
uxa dec -989 if wn <= 939
jq inc -390 if x != -1013
js inc 251 if g < 385
jq inc -572 if tyg <= 1424
g inc -265 if vyy > 3122
rjx inc 789 if x > -1025
gcf dec -838 if d < -465
g dec -564 if gcf != -387
vyy dec -188 if yzp != 3087
i dec 912 if x < -1015
cty inc -768 if x <= -1019
wn dec 175 if wow == 2906
wow inc 534 if qc > -3627
js inc 247 if x >= -1026
vyy dec 894 if gy == 944
x inc -150 if rf != -445
dma dec 766 if wn < 932
gcf dec -53 if zp >= 5383
g dec 9 if u >= -4740
yzp dec -425 if vyy < 2423
aqr inc 407 if vyy > 2406
gcf inc -244 if tyg != 1429
i inc 120 if i <= 2010
cty dec -40 if rf == -455
x dec -433 if wow <= 2900
u dec -553 if cty != 162
jq dec 329 if u <= -4177
aqr dec -319 if g > 387
esb dec 259 if wow > 2904
jq dec -590 if vyy < 2415
tyg dec -211 if d == -467
rjx dec -209 if l != -3561
tyg inc -564 if aqr >= 281
aqr dec -860 if u != -4186
wn inc -298 if g >= 387
x inc -951 if i < 2122
j inc -141 if cty >= 163
l inc 780 if wow != 2910
zp dec 796 if esb > -3491
j dec 652 if qc < -3628
cn dec 101 if i <= 2128
cty inc -169 if gcf < -573
dma dec -544 if epp <= -309
vyy dec -261 if zp <= 4598
rf inc 166 if esb == -3487
aqr dec 865 if rf == -455
u dec -14 if rjx <= 148
vyy inc -518 if dma < 538
aqr dec -30 if cn <= 1988
rf dec 818 if wow <= 2912
js inc 116 if l > -2786
jq inc 707 if gy > 939
jq dec -673 if x < -1176
wow dec 94 if rjx >= 141
esb inc -654 if esb > -3488
jq inc 982 if i != 2127
cn inc 479 if i > 2122
js dec 530 if rjx >= 144
wn dec -37 if gcf != -578
esb dec -917 if cn > 2458
l dec 519 if wn > 923
uxa dec 671 if wn == 933
zp inc -269 if cn >= 2457
esb inc -329 if wn == 933
tyg inc -490 if d <= -468
dma dec 817 if wn > 930
cty inc -650 if u != -4164
rf inc 804 if l >= -3309
dma dec 629 if esb == -3549
l dec -588 if epp < -317
zp dec 738 if zp >= 4318
l dec -772 if wn != 924
epp dec -423 if js <= -317
g dec 781 if qc != -3637
uxa inc -540 if tyg > 1062
gcf dec 120 if j != 1127
d inc 294 if wow >= 2819
i inc 108 if u >= -4169
x dec -117 if zp > 3581
i inc -434 if gy > 950
jq dec -749 if zp >= 3587
gcf dec -342 if tyg != 1063
j inc -910 if wn != 932
u inc -353 if rjx > 142
qc inc -478 if esb == -3549
uxa inc -992 if wn != 933
cty dec -628 if gcf == -356
u dec -527 if dma != -916
aqr inc -354 if j >= 211
d dec 633 if x >= -1062
l dec 920 if js != -326
wn dec -122 if j > 203
x dec 907 if gcf == -356
epp inc 112 if epp != 105
wn dec 322 if u >= -3988
j inc 934 if wn != 1055
g inc -366 if uxa >= 448
uxa dec -720 if wn <= 1063
zp inc 8 if gy <= 947
esb dec -199 if epp <= 110
cn dec -122 if j != 220
l dec -810 if g <= -763
cty inc -435 if yzp < 3521
zp dec 615 if i >= 2230
jq dec -445 if uxa != 1170
gy inc -654 if u > -3994
tyg dec 48 if dma == -914
gcf inc -346 if dma < -905
wn inc -660 if zp >= 2980
x inc -242 if esb >= -3359
gy inc 28 if rjx < 154
tyg dec 602 if esb <= -3341
jq dec 380 if l > -2061
i inc 502 if js <= -308
uxa inc -255 if qc < -4109
u dec -617 if l == -2051
rjx inc -864 if esb <= -3347
u dec -465 if vyy == 2157
tyg dec 629 if i < 2740
d inc -28 if u < -2907
epp inc -430 if cn <= 2585
vyy dec -740 if yzp == 3515
js inc 387 if gy > 315
vyy dec 792 if gy >= 310
l inc -89 if wn > 389
qc dec -149 if wow > 2810
gy inc 510 if cn == 2583
d inc 381 if g != -757
x inc 633 if gcf != -694
wn dec -677 if j > 222
wn inc -605 if i >= 2729
zp dec 794 if rf < -474
dma inc -560 if js >= 61
rjx dec -364 if wow <= 2819
jq inc 429 if g != -774
rjx dec -305 if j <= 215
epp inc -254 if tyg <= -219
i dec -106 if qc < -3955
g inc -514 if zp < 2983
dma inc 617 if u >= -2911
gy dec -81 if aqr > -40
g inc -722 if wn < -201
zp dec -46 if tyg >= -210
yzp dec 720 if gy <= 830
cty inc 675 if epp >= -318
qc dec 727 if cn >= 2574
zp dec -458 if wow != 2811
jq inc -547 if yzp <= 2800
uxa dec 443 if l == -2140
x dec 76 if tyg == -212
x inc 11 if aqr != -36
x dec 1000 if aqr <= -37
l dec -384 if gy != 822
u dec -329 if aqr == -40
x inc 432 if wn > -202
uxa inc 530 if tyg < -202
i dec -798 if js < 71
dma inc -503 if i == 3645
dma inc 69 if uxa <= 1264
d dec 571 if js != 70
wn inc 134 if u >= -2588
i dec -813 if rjx > -48
epp inc -735 if cn < 2585
aqr dec -223 if dma >= -790
uxa dec -86 if dma >= -789
cty inc 127 if aqr < 188
cty inc 472 if uxa == 1349
cn inc 780 if cty >= 791
cn dec -528 if rjx == -49
l inc 669 if d != -754
gcf dec 427 if epp != -1052
rf inc 465 if dma >= -797
epp inc 452 if g != -2005
epp dec -922 if i != 3648
wow inc -516 if js != 72
esb dec -623 if epp == 314
wn inc 434 if cn == 3111
rjx inc 698 if yzp == 2794
vyy dec -150 if epp < 319
rjx inc 343 if yzp != 2797
jq inc -390 if gy <= 831
yzp dec 296 if l >= -1093
yzp dec 676 if esb > -2730
js dec 320 if epp < 318
jq inc 44 if g < -1996
esb inc 425 if zp >= 3444
i inc -817 if esb == -2727
cty inc -336 if esb != -2727
epp inc -90 if uxa < 1341
zp dec 554 if epp != 312
js dec -299 if epp != 319
zp dec 92 if wn <= 366
wow dec -443 if rf > -12
gy dec -962 if i < 2825
vyy inc 381 if d > -748
wn dec -212 if js <= 54
esb dec -944 if gcf != -1127
cty dec 985 if j != 211
aqr dec 697 if uxa >= 1340
wow dec 459 if gcf < -1120
i inc 728 if dma >= -796
cty inc -277 if tyg >= -216
rjx inc 279 if aqr == -505
yzp inc -38 if zp >= 2793
zp dec 221 if epp == 314
d dec -628 if x <= -2630
uxa dec -846 if esb == -1783
rjx dec 154 if x <= -2625
l inc 541 if wow >= 2290
wow inc -777 if vyy < 2636
rjx dec -492 if uxa >= 2195
gy inc 881 if yzp < 1791
x dec 24 if l >= -1095
jq inc -82 if x >= -2658
tyg dec 763 if aqr > -519
wn dec -242 if esb < -1773
tyg inc 574 if d == -119
d dec 423 if i > 3540)";
 

Day8_1("puzzle", input1 + input2);

}