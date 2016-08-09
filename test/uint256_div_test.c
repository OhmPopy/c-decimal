#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arch_priv_uint256.h"

#include "mg_assert.h"

static void div_test(const char *text1, const char *text2, const char *ret1, const char *ret2)
{
	char strbuf1[1024];
	char strbuf2[1024];
	mg_uint256 v1, v2, v3;

	mg_uint256_test_convert(text1, &v1);
	mg_uint256_test_convert(text2, &v2);

	mg_uint256_div(&v1, &v2, &v3);

	mg_uint256_test_to_string(&v1, strbuf1);
	mg_uint256_test_to_string(&v3, strbuf2);

	mg_assert(strcmp(ret1, strbuf2) == 0);
	mg_assert(strcmp(ret2, strbuf1) == 0);
}

static void div_mul_test(const char *text1, const char *text2)
{
	char strbuf[1024];
	mg_uint256 v1, v2, v3, v4;

	mg_uint256_test_convert(text1, &v1);
	mg_uint256_test_convert(text2, &v2);

	mg_uint256_div(&v1, &v2, &v3);

	int overflow;
	mg_uint256_mul(&v2, &v3, &v4, &overflow);
	mg_assert(overflow == 0);
	mg_uint256_add(&v1, &v4);

	mg_uint256_test_to_string(&v1, strbuf);

	mg_assert(strcmp(text1, strbuf) == 0);
}

void mg_uint256_div_test()
{
	div_test("0", "10000000000000000000000999", "0", "0");
	div_test("0", "-10000000000000000000000999", "0", "0");
	div_test("9854613211238671786177861544111354141514014514", "25418761867546101656151465456897", "387690528067015", "19244209223450666204512304062059");
	div_test("9854613211238671786177861544111354141514014514", "25418761867546101656151465", "387690528067015757086", "20476374792925265450983524");
	div_test("9854613211238671786177861544111354141514014514", "2541876186754610165615", "3876905280670157570868279", "148466402025973987929");
	div_test("9854613211238671786177861544111354141514014514", "25418761867546", "387690528067017307560713303022313", "19143525460616");
	div_test("9854613211238671786177861544111354141514014514", "254187618", "38769052909723839444366096322250260598", "229138950");
	div_test("9854613211238671786177861544111354141514014514", "254", "38797689808026266874715990331147063549267773", "172");
	div_test("9854613211238671786177861544111354141514014514", "1", "9854613211238671786177861544111354141514014514", "0");
	div_test("9854613211238671786177861544111354141514014514", "25418761867546101656151465456897", "387690528067015", "19244209223450666204512304062059");
	div_test("98546132112386717861778615441113541415", "9854613211238671786177861544111354141514014514", "0", "98546132112386717861778615441113541415");
	div_test("9854613211238671786177861544", "9854613211238671786177861544111354141514014514", "0", "9854613211238671786177861544");
	div_test("98546132112386717861", "9854613211238671786177861544111354141514014514", "0", "98546132112386717861");
	div_test("98546132112386", "9854613211238671786177861544111354141514014514", "0", "98546132112386");
	div_test("985461321", "9854613211238671786177861544111354141514014514", "0", "985461321");
	div_test("1", "9854613211238671786177861544111354141514014514", "0", "1");
	div_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "115792089237316195423570985008687907853269984665640564039457584007913129639935", "1", "0");
	div_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "1157920892373161954235709850086879078532699846656405640394575840079131", "100000000", "29639935");
	div_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "11579208923731619542357098500868790785326998466564056403945", "10000000000000000000", "7584007913129639935");
	div_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "115792089237316195423570985008687907853269984665", "1000000000000000000000000000000", "640564039457584007913129639935");
	div_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "1157920892373161954235709850086879078", "100000000000000000000000000000000000046004", "991932905621496797988064516344535623");
	div_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "115792089237316195423570", "1000000000000000000000008506701057004639924327326279277", "53878062157330001281045");
	div_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "115792089237", "1000000000002730716974315966315928749125468071682380918533504532554", "76390118637");
	div_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "115", "1006887732498401699335399869640764416115391171005570122082239860938375040347", "30");
	div_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "1", "115792089237316195423570985008687907853269984665640564039457584007913129639935", "0");
	div_test("99999999999999999999999999999999999999999999999999999999999999999999999999999", "99999999999999999999999999999999999999999999999999999999999999999999999999999", "1", "0");
	div_test("99999999999999999999999999999999999999999999999999999999999999999999999999999", "999999999999999999999999999999999999999999999999999999999999999999", "100000000000", "99999999999");
	div_test("99999999999999999999999999999999999999999999999999999999999999999999999999999", "999999999999999999999999999999999999999999999999999999", "100000000000000000000000", "99999999999999999999999");
	div_test("99999999999999999999999999999999999999999999999999999999999999999999999999999", "99999999999999999999999999999999999999999", "1000000000000000000000000000000000000", "999999999999999999999999999999999999");
	div_test("99999999999999999999999999999999999999999999999999999999999999999999999999999", "9999999999999999999999999999", "10000000000000000000000000001000000000000000000000", "999999999999999999999");
	div_test("99999999999999999999999999999999999999999999999999999999999999999999999999999", "99999999999999999", "1000000000000000010000000000000000100000000000000001000000000", "999999999");
	div_test("99999999999999999999999999999999999999999999999999999999999999999999999999999", "99999999999", "1000000000010000000000100000000001000000000010000000000100000000001", "0");
	div_test("99999999999999999999999999999999999999999999999999999999999999999999999999999", "999", "100100100100100100100100100100100100100100100100100100100100100100100100100", "99");
	div_test("99999999999999999999999999999999999999999999999999999999999999999999999999999", "9", "11111111111111111111111111111111111111111111111111111111111111111111111111111", "0");
	div_test("99999999999999999999999999999999999999999999999999999999999999999999999999999", "99999999999999999999999999999999999999999999999999999999999999999999999999999", "1", "0");
	div_test("99999999999999999999999999999999999999999999999999999999999999999", "99999999999999999999999999999999999999999999999999999999999999999999999999999", "0", "99999999999999999999999999999999999999999999999999999999999999999");
	div_test("999999999999999999999999999999999999999999999999999999", "99999999999999999999999999999999999999999999999999999999999999999999999999999", "0", "999999999999999999999999999999999999999999999999999999");
	div_test("9999999999999999999999999999999999999999", "99999999999999999999999999999999999999999999999999999999999999999999999999999", "0", "9999999999999999999999999999999999999999");
	div_test("99999999999999999999999999999", "99999999999999999999999999999999999999999999999999999999999999999999999999999", "0", "99999999999999999999999999999");
	div_test("9999999999999999999", "99999999999999999", "100", "99");
	div_test("99999999999", "99999999999999999999999999999999999999999999999999999999999999999999999999999", "0", "99999999999");
	div_test("9999", "99999999999999999999999999999999999999999999999999999999999999999999999999999", "0", "9999");
	div_test("9", "99999999999999999999999999999999999999999999999999999999999999999999999999999", "0", "9");
	div_test("340282366920938463463374607431768211455", "340282366920938463463374607431768211455", "1", "0");
	div_test("340282366920938463463374607431768211455", "340282366920938463463374607431", "1000000000", "768211455");
	div_test("340282366920938463463374607431768211455", "34028236692093846346", "10000000000000000000", "3374607431768211455");
	div_test("340282366920938463463374607431768211455", "34028236692", "10000000000027578962491325303", "24515593779");
	div_test("340282366920938463463374607431768211455", "3402", "100024211323027179148552206770067081", "1893");
	div_test("340282366920938463463374607431768211455", "3", "113427455640312821154458202477256070485", "0");
	div_test("18446744073709551615", "18446744073709551615", "1", "0");
	div_test("18446744073709551615", "1844674407370", "10000000", "9551615");
	div_test("18446744073709551615", "184467", "100000238924629", "13872");
	div_test("18446744073709551615", "184", "100254043878856258", "143");
	div_test("18446744073709551615", "1", "18446744073709551615", "0");
	div_test("18446744073709551616", "18446744073709551616", "1", "0");
	div_test("18446744073709551616", "16", "1152921504606846976", "0");
	div_test("18446744073709551616", "8", "2305843009213693952", "0");
	div_test("18446744073709551616", "4", "4611686018427387904", "0");
	div_test("18446744073709551616", "2", "9223372036854775808", "0");
	div_test("79228162514264337593543950336", "79228162514264337593543950336", "1", "0");
	div_test("79228162514264337593543950336", "18446744073709551616", "4294967296", "0");
	div_test("79228162514264337593543950336", "340282366920938463463374607431768211456", "0", "79228162514264337593543950336");
	div_test("340282366920938463463374607431768211456", "79228162514264337593543950336", "4294967296", "0");
	div_test("8914056846084040561561132010123", "12551465013521508975356544561", "710", "2516686483769189057985371813");
	div_test("8914056846084040561561132010123", "1255146501352150897535", "7102005093", "1019933500763040864368");
	div_test("8914056846084040561561132010123", "125514650135215", "71020050938126062", "46154116536793");
	div_test("8914056846084040561561132010123", "125514650", "71020051014634869806521", "80977473");
	div_test("8914056846084040561561132010123", "1255", "7102834140306008415586559370", "773");
	div_test("8914056846084040561561132010123", "1", "8914056846084040561561132010123", "0");
	div_test("4952", "330", "15", "2");
	div_test("90000001", "852", "105633", "685");
	div_test("852", "3", "284", "0");
	div_test("852", "2", "426", "0");
	div_test("852", "64", "13", "20");
	div_test("852", "999", "0", "852");
	div_test("530000", "270", "1962", "260");
	div_test("986500", "999", "987", "487");
	div_test("5968", "2", "2984", "0");
	div_test("9996550", "355", "28159", "105");
	div_test("7800", "100", "78", "0");
	div_test("7800", "320", "24", "120");
	div_test("7800", "8", "975", "0");
	div_test("7800", "96", "81", "24");
	div_test("33076", "33076", "1", "0");
	div_test("33076", "365", "90", "226");
	div_test("33076001551", "365", "90619182", "121");
	div_test("26959946660873538060741835960174461801791452538186943042387869433855", "26959946660873538060741835960174461801791452538186943042387869433855", "1", "0");
	div_test("26959946660873538060741835960174461801791452538186943042387869433855", "1461501636990620551361974531748726005748293697535", "18446744073709551616", "4294967295");
	div_test("26959946660873538060741835960174461801791452538186943042387869433855", "79228162495817593524129366015", "340282366920938463463374607431768211457", "0");
	div_test("26959946660873538060741835960174461801791452538186943042387869433855", "4294967295", "6277101735386680764176071790128604879584176795969512275969", "0");
	div_test("1766820105243087041267848467410591083712559083657179364930612997358944255", "1766820105243087041267848467410591083712559083657179364930612997358944255", "1", "0");
	div_test("1766820105243087041267848467410591083712559083657179364930612997358944255", "411369862324345633682759587515748823925982947381487899676573695", "4294967296", "65535");
	div_test("1766820105243087041267848467410591083712559083657179364930612997358944255", "95779509824781127665834405346715083328537397873934335", "18446744073709551616", "281470681808895");
	div_test("1766820105243087041267848467410591083712559083657179364930612997358944255", "22300404921355919834653475635385858670002175", "79228162514264337593543950336", "1208907373152026146963455");
	div_test("1766820105243087041267848467410591083712559083657179364930612997358944255", "5192217631581220737344928932233215", "340282366920938463463374607431768211457", "0");
	div_test("1766820105243087041267848467410591083712559083657179364930612997358944255", "1208907373152026146963455", "1461501637330902918203684832734729763729642094592", "281470681808895");
	div_test("1766820105243087041267848467410591083712559083657179364930612997358944255", "281470681808895", "6277101735386680764176071790128604879584176795969512275969", "0");
	div_test("1766820105243087041267848467410591083712559083657179364930612997358944255", "65535", "26959946673427741531515197488526605382048662297355296634326893985793", "0");
	div_test("115792089210356248762697446947946071893095522863849111501270640965525260206080", "115792089210356248762697446947946071893095522863849111501270640965525260206080", "1", "0");
	div_test("115792089210356248762697446947946071893095522863849111501270640965525260206080", "6277101733925179126845168871845691884353629438715740815360", "18446744073709551616", "18446744069414584320");
	div_test("115792089210356248762697446947946071893095522863849111501270640965525260206080", "340282366841710300967557013907638845440", "340282366920938463463374607431768211457", "0");
	div_test("115792089210356248762697446947946071893095522863849111501270640965525260206080", "18446744069414584320", "6277101735386680764176071790128604879584176795969512275969", "0");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "115790322417210952336529717160220497262186272106556906860092653394915770695680", "1", "0");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "26959535297288315449033332327432114924813218439593190993203933675520", "4294967296", "4294901760");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "6277005955876855982708123588802319701019026907066160578560", "18446744073709551616", "18446462603027742720");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "1461479336925981562283850179240647633797262540800", "79228162514264337593543950336", "79226953606891185567396986880");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "340277174703306882242637262502835978240", "340282366920938463463374607431768211457", "0");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "79226953606891185567396986880", "1461501637330902918203684832734729763729642094592", "18446462603027742720");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "18446462603027742720", "6277101735386680764176071790128604879584176795969512275969", "0");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "4294901760", "26959946673427741531515197488526605382048662297355296634326893985793", "0");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "411369862324345633682759587515748823925982947381487899676573695", "281474976710656", "4294901760");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "1532472157196498042653350485547441333256598365982949360", "75557863725914323419136", "18446462603027742720");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "22300404921355919834653475635385858670002175", "5192296858534827628530496329220096", "79226953606891185567396986880");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "5192217631581220737344928932233215", "22300745198530623141535718272648361506045952", "0");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "1208907373152026146963455", "95780971304118053647396689198103249795785824311181312", "18446462603027742720");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "281470681808895", "411376139330301510561043040837868249388428610500657956517904384", "0");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "65535", "1766847065189760469009379982608079610317941132319476720227247324252930048", "0");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "409769201381449347170375308965103886867905192722415962323746560", "282574488338432", "4294901760");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "1526509230514799606689718771595894868924860629150330880", "75853011631093676244992", "18446462603027742720");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "22213632917770877345024473784664512916422400", "5212579268138479298954443580506112", "79226953606891185567396986880");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "5172014450135379411518684072574720", "22387857484462383388182342172150894168178944", "0");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "1204203453412134994640640", "96155115723274764794456832515283340615300612687396864", "18446462603027742720");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "280375465148160", "412983077374560500836672115216141172237602159760426151660552448", "0");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "65280", "1773748811538157970841447873165142421295745589867599676165635009113293056", "0");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "1828338397023562246760331670977544066880064019777104863442006", "63330903407001375", "1418603346028169453240471395692984980995309852343414095937430");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "6811091292737283731849237050777465354204416348699870", "17000259934950367899030421", "6289999229741924892702357690652708674011698841950410");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "25373292314772619798217851857757066764698983", "4563472527756932344343993266905402", "2471895899281848707864800680962975304089514");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "94522879700260683142460330790866415", "1224997828931904791015128853462681321806194", "85126408311899152946846569797121170");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "5634002667681019493488093065", "20552053175521615970295676044823871644318039206934", "4477679612557039151185382970");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "5124095576030430", "22597221441156685967341394337456889510699762747506236811786985", "4115854732742130");
	div_test("115790322417210952336529717160220497262186272106556906860092653394915770695680", "305419896", "379118465868415305650322522407710129212362354109887153062525610299192", "21171648");
	div_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "1828338397023562246760331670977544066880064019777104863442006", "63331869759897600", "1412347890462003173088069141137103413153711050240791031054335");
	div_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "6811091292737283731849237050777465354204416348699870", "17000519338330722976665600", "18451811346287888213319427989749005376167935");
	div_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "25373292314772619798217851857757066764698983", "4563542160821625901050907695513600", "18451811348742059758285202938924189546971135");
	div_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "94522879700260683142460330790866415", "1225016520915378483410011286459102566333200", "242128734531298675550161935");
	div_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "5634002667681019493488093065", "20552366774965822537922175917810395446070424430921", "4039482775395398521017977070");
	div_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "5124095576030430", "22597566247392055179468581553557009397319493884022769804902400", "170967549607935");
	div_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "305419896", "379124250757115690405352587143464641390847650166315831760539870028353", "39328647");


	div_mul_test("5468716165", "6576141");
	div_mul_test("10000000", "3");
	div_mul_test("89", "3");
	div_mul_test("566726574564156372054607488056048544890489", "4545612101");
	div_mul_test("566726574564156372", "6054987415246054607488056048544890489");
	div_mul_test("5667265745641563726054987415246054607488056048544890489", "6054956048544890489");
	div_mul_test("888888", "2");
	div_mul_test("999999", "2");
	div_mul_test("999999999999", "2");
	div_mul_test("99999999999999999999999999", "2");
	div_mul_test("99999999999999999999999999999999999999", "2");
	div_mul_test("99999999999999999999999999999999999999", "33");
	div_mul_test("99999999999999999999999999999999999999", "33333333333333333333333333333333");
	div_mul_test("9999999999999999999999999999999999999999999999", "33333333333333333333333333333333");
	div_mul_test("9999999999999999999999999999999999999999999999", "9999999999999999999999999999999999999999999999");
	div_mul_test("99999999999999999999999999999999999999999999999999999999", "99999999999999999999999999999999999999999999999999999998");
	div_mul_test("99999999999999999999999999999999999999999999999999999999", "1");
	div_mul_test("99999999999999999999999999999999999999999999999999999999", "3");
	div_mul_test("3", "99999999999999999999999999999999999999999999999999999999");
	div_mul_test("7", "99999999999999999999999999999999999999999999999999999999");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "115792089237316195423570985008687907853269984665640564039457584007913129639935");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "340282366920938463463374607431768211455");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "340282366920938463463374607431768211456");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "100000000000000000000000000000000000000000000000000000000000000000000000000000");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "10000000000000000000000000000000000000000000000000000000000000000000");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "10000000000000000000000000000000000000000000000000000000000");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "1000000000000000000000000000000000000000000000000");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "10000000000000000000000000000000000000000");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "1000000000000000000000000000000");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "10000000000000000000000");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "10000000000000");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "10000000");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "100");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "1157");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "11579208");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "115792089237");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "99");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "90");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "70");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "40");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "10");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "9");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "8");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "5");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "3");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "2");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "1");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "101001");
	div_mul_test("340282366920938463463374607431768211455", "1000000000000000000000000000000000000000000000000000000000000000000000000");
	div_mul_test("340282366920938463463374607431768211455", "10000000000000000000000000000000000000000000000000000000000000000");
	div_mul_test("340282366920938463463374607431768211455", "1000000000000000000000000000000000000000000000000000000");
	div_mul_test("340282366920938463463374607431768211455", "1000000000000000000000000000000000000000000000");
	div_mul_test("340282366920938463463374607431768211455", "100000000000000000000000000000000000");
	div_mul_test("340282366920938463463374607431768211455", "100000000000000000000000000");
	div_mul_test("340282366920938463463374607431768211455", "1000000000000000000");
	div_mul_test("340282366920938463463374607431768211455", "100000000");
	div_mul_test("340282366920938463463374607431768211455", "100");
	div_mul_test("340282366920938463463374607431768211455", "1");
	div_mul_test("340282366920938463463374607431768211455", "2");
	div_mul_test("340282366920938463463374607431768211455", "5");
	div_mul_test("340282366920938463463374607431768211455", "7");
	div_mul_test("340282366920938463463374607431768211455", "9");
	div_mul_test("340282366920938463463374607431768211455", "10");
	div_mul_test("340282366920938463463374607431768211455", "340282366920938463463374607431768211455");
	div_mul_test("340282366920938463463374607431768211455", "12123");
	div_mul_test("340282366920938463463374607431768211455", "256");
	div_mul_test("340282366920938463463374607431768211455", "1024");
	div_mul_test("340282366920938463463374607431768211455", "1");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "340282366920938463463374607431768211455");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "18446744073709551616");
	div_mul_test("9897238645340312564123213455452154145", "9462238455652");
	div_mul_test("78456513564212", "9462");
	div_mul_test("1", "1");
	div_mul_test("1", "2");
	div_mul_test("1", "3");
	div_mul_test("10", "3");
	div_mul_test("10", "2");
	div_mul_test("1237894111111", "340282366920938463463374607431768211455");
	div_mul_test("100000000000000000000000000000000000000000000000000000000000000000000000", "2");
	div_mul_test("100000000000000000000000000000000000000000000000000000000000000000000000", "9");
	div_mul_test("100000000000000000000000000000000000000000000000000000000000000000000000", "35412636");
	div_mul_test("100000000000000000000000000000000000000000000000000000000000000000000000", "3402823669209384635");
	div_mul_test("100000000000000000000000000000000000000000000000000000000000000000000000", "340282366920938463463374607431768211455");
	div_mul_test("97456415132141", "97456415132141");
	div_mul_test("99999999999999994809489840894890840045600400", "97456415132141");
	div_mul_test("415146", "304");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "115792089237316195423570985008687907853269984665640564039457584007913");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "11579208923731619542357098500868790785326998466564056403945");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "11579208923731619542357098500868790785326998466564");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "11579208923731619542357098500868790785326");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "115792089237316195423570985008687");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "115792089237316195423570");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "11579208923731619");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "1157920892");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "1157");
	div_mul_test("115792089237316195423570985008687907853269984665640564039457584007913129639935", "1");
	div_mul_test("100000000000000000000000000000000", "10000000000000000000000000000000");
	div_mul_test("100000000000000000000000000000000", "10000000000000000000000000000");
	div_mul_test("100000000000000000000000000000000", "100000000000000000000000");
	div_mul_test("100000000000000000000000000000000", "1000000000000000000");
	div_mul_test("100000000000000000000000000000000", "1000000000000");
	div_mul_test("100000000000000000000000000000000", "1000000");
	div_mul_test("100000000000000000000000000000000", "10");
	div_mul_test("10000000000000000000000000000", "100000000000000000000000000000000");
	div_mul_test("100000000000000000000000", "100000000000000000000000000000000");
	div_mul_test("1000000000000000000", "100000000000000000000000000000000");
	div_mul_test("1000000000000", "100000000000000000000000000000000");
	div_mul_test("1000000", "100000000000000000000000000000000");
	div_mul_test("100000000000000000000000000", "100000000000000000000000000");
	div_mul_test("100000000000000000000000000", "10000000000000000000000");
	div_mul_test("100000000000000000000000000", "100000000000000000");
	div_mul_test("100000000000000000000000000", "100000000000000");
	div_mul_test("100000000000000000000000000", "1000000000000");
	div_mul_test("100000000000000000000000000", "1000000");
	div_mul_test("100000000000000000000000000", "10");
	div_mul_test("100000000000000000000000000", "100000000000000000000000000");
	div_mul_test("10000000000000000000000", "100000000000000000000000000");
	div_mul_test("100000000000000000", "100000000000000000000000000");
	div_mul_test("100000000000000", "100000000000000000000000000");
	div_mul_test("1000000000000", "100000000000000000000000000");
	div_mul_test("1000000", "100000000000000000000000000");
	div_mul_test("10", "100000000000000000000000000");
	div_mul_test("10000000000000000000000", "10000000000000000000000");
	div_mul_test("10000000000000000000000", "100000000000000000");
	div_mul_test("10000000000000000000000", "100000000000000");
	div_mul_test("10000000000000000000000", "1000000000000");
	div_mul_test("10000000000000000000000", "1000000");
	div_mul_test("10000000000000000000000", "10");
	div_mul_test("10000000000000000000000", "10000000000000000000000");
	div_mul_test("100000000000000000", "10000000000000000000000");
	div_mul_test("100000000000000", "10000000000000000000000");
	div_mul_test("1000000000000", "10000000000000000000000");
	div_mul_test("1000000", "10000000000000000000000");
	div_mul_test("10", "10000000000000000000000");
	div_mul_test("100000000000000000", "100000000000000000");
	div_mul_test("100000000000000000", "100000000000000");
	div_mul_test("100000000000000000", "1000000000000");
	div_mul_test("100000000000000000", "1000000");
	div_mul_test("100000000000000000", "10");
	div_mul_test("100000000000000000", "100000000000000000");
	div_mul_test("1000000000000", "100000000000000000");
	div_mul_test("1000000", "100000000000000000");
	div_mul_test("10", "100000000000000000");
	div_mul_test("10000000000000", "10000000000000");
	div_mul_test("10000000000000", "1000000");
	div_mul_test("10000000000000", "10");
	div_mul_test("10000000000000", "10000000000000");
	div_mul_test("1000000", "10000000000000");
	div_mul_test("10", "10000000000000");
	div_mul_test("10000000", "10000000");
	div_mul_test("10000000", "10000");
	div_mul_test("10000000", "10");
	div_mul_test("10000000", "10000000");
	div_mul_test("10000", "10000000");
	div_mul_test("10", "10000000");
	div_mul_test("10000000", "10000000");
	div_mul_test("10000000", "10000");
	div_mul_test("10000000", "10");
	div_mul_test("10000000", "10000000");
	div_mul_test("10000", "10000000");
	div_mul_test("10", "10000000");

	printf("TEST mg_uint256_div(): OK\n");
}
