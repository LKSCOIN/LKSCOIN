static int coinsforblocks(int prevblock)
{
    int coin = 500;//

    if(prevblock>=0 && prevblock<=39)
    {
        coin = 50000000;
    }
    if(prevblock>39 && prevblock<=8039)
    {
        coin = 10000;
    }
    if(prevblock>8039 && prevblock<=44319)
    {
        coin = 45;
    }
    //Jackpots
    if( prevblock==48989 || prevblock==399062 || prevblock==749135 || prevblock==1099208 || prevblock==1449281 || prevblock==1799354 || prevblock==2149427 || prevblock==2499500 || prevblock==2849573 || prevblock==3199646 )
    {
    coin = 100000;
    }
    if( prevblock==53659 || prevblock==403732 || prevblock==753805 || prevblock==1103878 || prevblock==1453951 || prevblock==1804024 || prevblock==2154097 || prevblock==2504170 || prevblock==2854243 || prevblock==3204316 )
    {
    coin = 100000;
    }
    if( prevblock==58329 || prevblock==408402 || prevblock==758475 || prevblock==1108548 || prevblock==1458621 || prevblock==1808694 || prevblock==2158767 || prevblock==2508840 || prevblock==2858913 || prevblock==3208986 )
    {
    coin = 200000;
    }
    if( prevblock==62999 || prevblock==413072 || prevblock==763145 || prevblock==1113218 || prevblock==1463291 || prevblock==1813364 || prevblock==2163437 || prevblock==2513510 || prevblock==2863583 || prevblock==3213656 )
    {
    coin = 100000;
    }
    if( prevblock==67669 || prevblock==417742 || prevblock==767815 || prevblock==1117888 || prevblock==1467961 || prevblock==1818034 || prevblock==2168107 || prevblock==2518180 || prevblock==2868253 || prevblock==3218326 )
    {
    coin = 100000;
    }
    if( prevblock==72339 || prevblock==422412 || prevblock==772485 || prevblock==1122558 || prevblock==1472631 || prevblock==1822704 || prevblock==2172777 || prevblock==2522850 || prevblock==2872923 || prevblock==3222996 )
    {
    coin = 200000;
    }
    if( prevblock==77009 || prevblock==427082 || prevblock==777155 || prevblock==1127228 || prevblock==1477301 || prevblock==1827374 || prevblock==2177447 || prevblock==2527520 || prevblock==2877593 || prevblock==3227666 )
    {
    coin = 100000;
    }
    if( prevblock==81679 || prevblock==431752 || prevblock==781825 || prevblock==1131898 || prevblock==1481971 || prevblock==1832044 || prevblock==2182117 || prevblock==2532190 || prevblock==2882263 || prevblock==3232336 )
    {
    coin = 100000;
    }
    if( prevblock==86349 || prevblock==436422 || prevblock==786495 || prevblock==1136568 || prevblock==1486641 || prevblock==1836714 || prevblock==2186787 || prevblock==2536860 || prevblock==2886933 || prevblock==3237006 )
    {
    coin = 200000;
    }
    if( prevblock==91019 || prevblock==441092 || prevblock==791165 || prevblock==1141238 || prevblock==1491311 || prevblock==1841384 || prevblock==2191457 || prevblock==2541530 || prevblock==2891603 || prevblock==3241676 )
    {
    coin = 100000;
    }
    if( prevblock==95689 || prevblock==445762 || prevblock==795835 || prevblock==1145908 || prevblock==1495981 || prevblock==1846054 || prevblock==2196127 || prevblock==2546200 || prevblock==2896273 || prevblock==3246346 )
    {
    coin = 1000000;
    }
    if( prevblock==100359 || prevblock==450432 || prevblock==800505 || prevblock==1150578 || prevblock==1500651 || prevblock==1850724 || prevblock==2200797 || prevblock==2550870 || prevblock==2900943 || prevblock==3251016 )
    {
    coin = 200000;
    }
    if( prevblock==105029 || prevblock==455102 || prevblock==805175 || prevblock==1155248 || prevblock==1505321 || prevblock==1855394 || prevblock==2205467 || prevblock==2555540 || prevblock==2905613 || prevblock==3255686 )
    {
    coin = 100000;
    }
    if( prevblock==109699 || prevblock==459772 || prevblock==809845 || prevblock==1159918 || prevblock==1509991 || prevblock==1860064 || prevblock==2210137 || prevblock==2560210 || prevblock==2910283 || prevblock==3260356 )
    {
    coin = 100000;
    }
    if( prevblock==114369 || prevblock==464442 || prevblock==814515 || prevblock==1164588 || prevblock==1514661 || prevblock==1864734 || prevblock==2214807 || prevblock==2564880 || prevblock==2914953 || prevblock==3265026 )
    {
    coin = 200000;
    }
    if( prevblock==119039 || prevblock==469112 || prevblock==819185 || prevblock==1169258 || prevblock==1519331 || prevblock==1869404 || prevblock==2219477 || prevblock==2569550 || prevblock==2919623 || prevblock==3269696 )
    {
    coin = 100000;
    }
    if( prevblock==123709 || prevblock==473782 || prevblock==823855 || prevblock==1173928 || prevblock==1524001 || prevblock==1874074 || prevblock==2224147 || prevblock==2574220 || prevblock==2924293 || prevblock==3274366 )
    {
    coin = 400000;
    }
    if( prevblock==128379 || prevblock==478452 || prevblock==828525 || prevblock==1178598 || prevblock==1528671 || prevblock==1878744 || prevblock==2228817 || prevblock==2578890 || prevblock==2928963 || prevblock==3279036 )
    {
    coin = 100000;
    }
    if( prevblock==133049 || prevblock==483122 || prevblock==833195 || prevblock==1183268 || prevblock==1533341 || prevblock==1883414 || prevblock==2233487 || prevblock==2583560 || prevblock==2933633 || prevblock==3283706 )
    {
    coin = 600000;
    }
    if( prevblock==137719 || prevblock==487792 || prevblock==837865 || prevblock==1187938 || prevblock==1538011 || prevblock==1888084 || prevblock==2238157 || prevblock==2588230 || prevblock==2938303 || prevblock==3288376 )
    {
    coin = 200000;
    }
    if( prevblock==142389 || prevblock==492462 || prevblock==842535 || prevblock==1192608 || prevblock==1542681 || prevblock==1892754 || prevblock==2242827 || prevblock==2592900 || prevblock==2942973 || prevblock==3293046 )
    {
    coin = 800000;
    }
    if( prevblock==147059 || prevblock==497132 || prevblock==847205 || prevblock==1197278 || prevblock==1547351 || prevblock==1897424 || prevblock==2247497 || prevblock==2597570 || prevblock==2947643 || prevblock==3297716 )
    {
    coin = 400000;
    }
    if( prevblock==151729 || prevblock==501802 || prevblock==851875 || prevblock==1201948 || prevblock==1552021 || prevblock==1902094 || prevblock==2252167 || prevblock==2602240 || prevblock==2952313 || prevblock==3302386 )
    {
    coin = 200000;
    }
    if( prevblock==156399 || prevblock==506472 || prevblock==856545 || prevblock==1206618 || prevblock==1556691 || prevblock==1906764 || prevblock==2256837 || prevblock==2606910 || prevblock==2956983 || prevblock==3307056 )
    {
    coin = 100000;
    }
    if( prevblock==161069 || prevblock==511142 || prevblock==861215 || prevblock==1211288 || prevblock==1561361 || prevblock==1911434 || prevblock==2261507 || prevblock==2611580 || prevblock==2961653 || prevblock==3311726 )
    {
    coin = 100000;
    }
    if( prevblock==165739 || prevblock==515812 || prevblock==865885 || prevblock==1215958 || prevblock==1566031 || prevblock==1916104 || prevblock==2266177 || prevblock==2616250 || prevblock==2966323 || prevblock==3316396 )
    {
    coin = 200000;
    }
    if( prevblock==170409 || prevblock==520482 || prevblock==870555 || prevblock==1220628 || prevblock==1570701 || prevblock==1920774 || prevblock==2270847 || prevblock==2620920 || prevblock==2970993 || prevblock==3321066 )
    {
    coin = 400000;
    }
    if( prevblock==175079 || prevblock==525152 || prevblock==875225 || prevblock==1225298 || prevblock==1575371 || prevblock==1925444 || prevblock==2275517 || prevblock==2625590 || prevblock==2975663 || prevblock==3325736 )
    {
    coin = 600000;
    }
    if( prevblock==179749 || prevblock==529822 || prevblock==879895 || prevblock==1229968 || prevblock==1580041 || prevblock==1930114 || prevblock==2280187 || prevblock==2630260 || prevblock==2980333 || prevblock==3330406 )
    {
    coin = 200000;
    }
    if( prevblock==184419 || prevblock==534492 || prevblock==884565 || prevblock==1234638 || prevblock==1584711 || prevblock==1934784 || prevblock==2284857 || prevblock==2634930 || prevblock==2985003 || prevblock==3335076 )
    {
    coin = 100000;
    }
    if( prevblock==189089 || prevblock==539162 || prevblock==889235 || prevblock==1239308 || prevblock==1589381 || prevblock==1939454 || prevblock==2289527 || prevblock==2639600 || prevblock==2989673 || prevblock==3339746 )
    {
    coin = 200000;
    }
    if( prevblock==193759 || prevblock==543832 || prevblock==893905 || prevblock==1243978 || prevblock==1594051 || prevblock==1944124 || prevblock==2294197 || prevblock==2644270 || prevblock==2994343 || prevblock==3344416 )
    {
    coin = 800000;
    }
    if( prevblock==198429 || prevblock==548502 || prevblock==898575 || prevblock==1248648 || prevblock==1598721 || prevblock==1948794 || prevblock==2298867 || prevblock==2648940 || prevblock==2999013 || prevblock==3349086 )
    {
    coin = 1000000;
    }
    if( prevblock==203099 || prevblock==553172 || prevblock==903245 || prevblock==1253318 || prevblock==1603391 || prevblock==1953464 || prevblock==2303537 || prevblock==2653610 || prevblock==3003683 || prevblock==3353756 )
    {
    coin = 400000;
    }
    if( prevblock==207769 || prevblock==557842 || prevblock==907915 || prevblock==1257988 || prevblock==1608061 || prevblock==1958134 || prevblock==2308207 || prevblock==2658280 || prevblock==3008353 || prevblock==3358426 )
    {
    coin = 200000;
    }
    if( prevblock==212439 || prevblock==562512 || prevblock==912585 || prevblock==1262658 || prevblock==1612731 || prevblock==1962804 || prevblock==2312877 || prevblock==2662950 || prevblock==3013023 || prevblock==3363096 )
    {
    coin = 200000;
    }
    if( prevblock==217109 || prevblock==567182 || prevblock==917255 || prevblock==1267328 || prevblock==1617401 || prevblock==1967474 || prevblock==2317547 || prevblock==2667620 || prevblock==3017693 || prevblock==3367766 )
    {
    coin = 600000;
    }
    if( prevblock==221779 || prevblock==571852 || prevblock==921925 || prevblock==1271998 || prevblock==1622071 || prevblock==1972144 || prevblock==2322217 || prevblock==2672290 || prevblock==3022363 || prevblock==3372436 )
    {
    coin = 200000;
    }
    if( prevblock==226449 || prevblock==576522 || prevblock==926595 || prevblock==1276668 || prevblock==1626741 || prevblock==1976814 || prevblock==2326887 || prevblock==2676960 || prevblock==3027033 || prevblock==3377106 )
    {
    coin = 400000;
    }
    if( prevblock==231119 || prevblock==581192 || prevblock==931265 || prevblock==1281338 || prevblock==1631411 || prevblock==1981484 || prevblock==2331557 || prevblock==2681630 || prevblock==3031703 || prevblock==3381776 )
    {
    coin = 100000;
    }
    if( prevblock==235789 || prevblock==585862 || prevblock==935935 || prevblock==1286008 || prevblock==1636081 || prevblock==1986154 || prevblock==2336227 || prevblock==2686300 || prevblock==3036373 || prevblock==3386446 )
    {
    coin = 200000;
    }
    if( prevblock==240459 || prevblock==590532 || prevblock==940605 || prevblock==1290678 || prevblock==1640751 || prevblock==1990824 || prevblock==2340897 || prevblock==2690970 || prevblock==3041043 || prevblock==3391116 )
    {
    coin = 100000;
    }
    if( prevblock==245129 || prevblock==595202 || prevblock==945275 || prevblock==1295348 || prevblock==1645421 || prevblock==1995494 || prevblock==2345567 || prevblock==2695640 || prevblock==3045713 || prevblock==3395786 )
    {
    coin = 400000;
    }
    if( prevblock==249799 || prevblock==599872 || prevblock==949945 || prevblock==1300018 || prevblock==1650091 || prevblock==2000164 || prevblock==2350237 || prevblock==2700310 || prevblock==3050383 || prevblock==3400456 )
    {
    coin = 800000;
    }
    if( prevblock==254469 || prevblock==604542 || prevblock==954615 || prevblock==1304688 || prevblock==1654761 || prevblock==2004834 || prevblock==2354907 || prevblock==2704980 || prevblock==3055053 || prevblock==3405126 )
    {
    coin = 200000;
    }
    if( prevblock==259139 || prevblock==609212 || prevblock==959285 || prevblock==1309358 || prevblock==1659431 || prevblock==2009504 || prevblock==2359577 || prevblock==2709650 || prevblock==3059723 || prevblock==3409796 )
    {
    coin = 600000;
    }
    if( prevblock==263809 || prevblock==613882 || prevblock==963955 || prevblock==1314028 || prevblock==1664101 || prevblock==2014174 || prevblock==2364247 || prevblock==2714320 || prevblock==3064393 || prevblock==3414466 )
    {
    coin = 200000;
    }
    if( prevblock==268479 || prevblock==618552 || prevblock==968625 || prevblock==1318698 || prevblock==1668771 || prevblock==2018844 || prevblock==2368917 || prevblock==2718990 || prevblock==3069063 || prevblock==3419136 )
    {
    coin = 1000000;
    }
    if( prevblock==273149 || prevblock==623222 || prevblock==973295 || prevblock==1323368 || prevblock==1673441 || prevblock==2023514 || prevblock==2373587 || prevblock==2723660 || prevblock==3073733 || prevblock==3423806 )
    {
    coin = 400000;
    }
    if( prevblock==277819 || prevblock==627892 || prevblock==977965 || prevblock==1328038 || prevblock==1678111 || prevblock==2028184 || prevblock==2378257 || prevblock==2728330 || prevblock==3078403 || prevblock==3428476 )
    {
    coin = 200000;
    }
    if( prevblock==282489 || prevblock==632562 || prevblock==982635 || prevblock==1332708 || prevblock==1682781 || prevblock==2032854 || prevblock==2382927 || prevblock==2733000 || prevblock==3083073 || prevblock==3433146 )
    {
    coin = 600000;
    }
    if( prevblock==287159 || prevblock==637232 || prevblock==987305 || prevblock==1337378 || prevblock==1687451 || prevblock==2037524 || prevblock==2387597 || prevblock==2737670 || prevblock==3087743 || prevblock==3437816 )
    {
    coin = 100000;
    }
    if( prevblock==291829 || prevblock==641902 || prevblock==991975 || prevblock==1342048 || prevblock==1692121 || prevblock==2042194 || prevblock==2392267 || prevblock==2742340 || prevblock==3092413 || prevblock==3442486 )
    {
    coin = 200000;
    }
    if( prevblock==296499 || prevblock==646572 || prevblock==996645 || prevblock==1346718 || prevblock==1696791 || prevblock==2046864 || prevblock==2396937 || prevblock==2747010 || prevblock==3097083 || prevblock==3447156 )
    {
    coin = 400000;
    }
    if( prevblock==301169 || prevblock==651242 || prevblock==1001315 || prevblock==1351388 || prevblock==1701461 || prevblock==2051534 || prevblock==2401607 || prevblock==2751680 || prevblock==3101753 || prevblock==3451826 )
    {
    coin = 600000;
    }
    if( prevblock==305839 || prevblock==655912 || prevblock==1005985 || prevblock==1356058 || prevblock==1706131 || prevblock==2056204 || prevblock==2406277 || prevblock==2756350 || prevblock==3106423 || prevblock==3456496 )
    {
    coin = 800000;
    }
    if( prevblock==310509 || prevblock==660582 || prevblock==1010655 || prevblock==1360728 || prevblock==1710801 || prevblock==2060874 || prevblock==2410947 || prevblock==2761020 || prevblock==3111093 || prevblock==3461166 )
    {
    coin = 100000;
    }
    if( prevblock==315179 || prevblock==665252 || prevblock==1015325 || prevblock==1365398 || prevblock==1715471 || prevblock==2065544 || prevblock==2415617 || prevblock==2765690 || prevblock==3115763 || prevblock==3465836 )
    {
    coin = 100000;
    }
    if( prevblock==319849 || prevblock==669922 || prevblock==1019995 || prevblock==1370068 || prevblock==1720141 || prevblock==2070214 || prevblock==2420287 || prevblock==2770360 || prevblock==3120433 || prevblock==3470506 )
    {
    coin = 400000;
    }
    if( prevblock==324519 || prevblock==674592 || prevblock==1024665 || prevblock==1374738 || prevblock==1724811 || prevblock==2074884 || prevblock==2424957 || prevblock==2775030 || prevblock==3125103 || prevblock==3475176 )
    {
    coin = 100000;
    }
    if( prevblock==329189 || prevblock==679262 || prevblock==1029335 || prevblock==1379408 || prevblock==1729481 || prevblock==2079554 || prevblock==2429627 || prevblock==2779700 || prevblock==3129773 || prevblock==3479846 )
    {
    coin = 100000;
    }
    if( prevblock==333859 || prevblock==683932 || prevblock==1034005 || prevblock==1384078 || prevblock==1734151 || prevblock==2084224 || prevblock==2434297 || prevblock==2784370 || prevblock==3134443 || prevblock==3484516 )
    {
    coin = 100000;
    }
    if( prevblock==338529 || prevblock==688602 || prevblock==1038675 || prevblock==1388748 || prevblock==1738821 || prevblock==2088894 || prevblock==2438967 || prevblock==2789040 || prevblock==3139113 || prevblock==3489186 )
    {
    coin = 1000000;
    }
    if( prevblock==343199 || prevblock==693272 || prevblock==1043345 || prevblock==1393418 || prevblock==1743491 || prevblock==2093564 || prevblock==2443637 || prevblock==2793710 || prevblock==3143783 || prevblock==3493856 )
    {
    coin = 600000;
    }
    if( prevblock==347869 || prevblock==697942 || prevblock==1048015 || prevblock==1398088 || prevblock==1748161 || prevblock==2098234 || prevblock==2448307 || prevblock==2798380 || prevblock==3148453 || prevblock==3498526 )
    {
    coin = 400000;
    }
    if( prevblock==352539 || prevblock==702612 || prevblock==1052685 || prevblock==1402758 || prevblock==1752831 || prevblock==2102904 || prevblock==2452977 || prevblock==2803050 || prevblock==3153123 || prevblock==3503196 )
    {
    coin = 100000;
    }
    if( prevblock==357209 || prevblock==707282 || prevblock==1057355 || prevblock==1407428 || prevblock==1757501 || prevblock==2107574 || prevblock==2457647 || prevblock==2807720 || prevblock==3157793 || prevblock==3507866 )
    {
    coin = 100000;
    }
    if( prevblock==361879 || prevblock==711952 || prevblock==1062025 || prevblock==1412098 || prevblock==1762171 || prevblock==2112244 || prevblock==2462317 || prevblock==2812390 || prevblock==3162463 || prevblock==3512536 )
    {
    coin = 800000;
    }
    if( prevblock==366549 || prevblock==716622 || prevblock==1066695 || prevblock==1416768 || prevblock==1766841 || prevblock==2116914 || prevblock==2466987 || prevblock==2817060 || prevblock==3167133 || prevblock==3517206 )
    {
    coin = 100000;
    }
    if( prevblock==371219 || prevblock==721292 || prevblock==1071365 || prevblock==1421438 || prevblock==1771511 || prevblock==2121584 || prevblock==2471657 || prevblock==2821730 || prevblock==3171803 || prevblock==3521876 )
    {
    coin = 200000;
    }
    if( prevblock==375889 || prevblock==725962 || prevblock==1076035 || prevblock==1426108 || prevblock==1776181 || prevblock==2126254 || prevblock==2476327 || prevblock==2826400 || prevblock==3176473 || prevblock==3526546 )
    {
    coin = 100000;
    }
    if( prevblock==380559 || prevblock==730632 || prevblock==1080705 || prevblock==1430778 || prevblock==1780851 || prevblock==2130924 || prevblock==2480997 || prevblock==2831070 || prevblock==3181143 || prevblock==3531216 )
    {
    coin = 600000;
    }
    if( prevblock==385229 || prevblock==735302 || prevblock==1085375 || prevblock==1435448 || prevblock==1785521 || prevblock==2135594 || prevblock==2485667 || prevblock==2835740 || prevblock==3185813 || prevblock==3535886 )
    {
    coin = 800000;
    }
    if( prevblock==389899 || prevblock==739972 || prevblock==1090045 || prevblock==1440118 || prevblock==1790191 || prevblock==2140264 || prevblock==2490337 || prevblock==2840410 || prevblock==3190483 || prevblock==3540556 )
    {
    coin = 1000000;
    }

    return coin;
}
