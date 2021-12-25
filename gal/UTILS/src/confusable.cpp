// ReSharper disable CommentTypo
// ReSharper disable StringLiteralTypo
#include <utils/confusable.hpp>

#include <compare>
#include <algorithm>

namespace
{
	struct confusable
	{
		unsigned codepoint;
		char text[5];

		friend constexpr bool operator==(const confusable& lhs, const confusable& rhs) noexcept
		{
			return lhs.codepoint == rhs.codepoint;
		}

		friend constexpr auto operator<=>(const confusable& lhs, const confusable& rhs) noexcept
		{
			return lhs.codepoint <=> rhs.codepoint;
		}
	};

	// https://www.unicode.org/Public/security/latest/confusables.txt
	constexpr confusable g_confusable[] =
	{
			{34, "\""},     // MA#* ( " �� '' ) QUOTATION MARK �� APOSTROPHE, APOSTROPHE# # Converted to a quote.
			{48, "O"},      // MA# ( 0 �� O ) DIGIT ZERO �� LATIN CAPITAL LETTER O#
			{49, "l"},      // MA# ( 1 �� l ) DIGIT ONE �� LATIN SMALL LETTER L#
			{73, "l"},      // MA# ( I �� l ) LATIN CAPITAL LETTER I �� LATIN SMALL LETTER L#
			{96, "'"},      // MA#* ( ` �� ' ) GRAVE ACCENT �� APOSTROPHE# ���A�������������
			{109, "rn"},    // MA# ( m �� rn ) LATIN SMALL LETTER M �� LATIN SMALL LETTER R, LATIN SMALL LETTER N#
			{124, "l"},     // MA#* ( | �� l ) VERTICAL LINE �� LATIN SMALL LETTER L#
			{160, " "},     // MA#* ( ? ��   ) NO-BREAK SPACE �� SPACE#
			{180, "'"},     // MA#* ( ? �� ' ) ACUTE ACCENT �� APOSTROPHE# ��?����?��
			{184, ","},     // MA#* ( ? �� , ) CEDILLA �� COMMA#
			{198, "AE"},    // MA# ( ? �� AE ) LATIN CAPITAL LETTER AE �� LATIN CAPITAL LETTER A, LATIN CAPITAL LETTER E#
			{215, "x"},     // MA#* ( �� �� x ) MULTIPLICATION SIGN �� LATIN SMALL LETTER X#
			{230, "ae"},    // MA# ( ? �� ae ) LATIN SMALL LETTER AE �� LATIN SMALL LETTER A, LATIN SMALL LETTER E#
			{305, "i"},     // MA# ( ? �� i ) LATIN SMALL LETTER DOTLESS I �� LATIN SMALL LETTER I#
			{306, "lJ"},    // MA# ( ? �� lJ ) LATIN CAPITAL LIGATURE IJ �� LATIN SMALL LETTER L, LATIN CAPITAL LETTER J# ��IJ��
			{307, "ij"},    // MA# ( ? �� ij ) LATIN SMALL LIGATURE IJ �� LATIN SMALL LETTER I, LATIN SMALL LETTER J#
			{329, "'n"},    // MA# ( ? �� 'n ) LATIN SMALL LETTER N PRECEDED BY APOSTROPHE �� APOSTROPHE, LATIN SMALL LETTER N# ��?n��
			{338, "OE"},    // MA# ( ? �� OE ) LATIN CAPITAL LIGATURE OE �� LATIN CAPITAL LETTER O, LATIN CAPITAL LETTER E#
			{339, "oe"},    // MA# ( ? �� oe ) LATIN SMALL LIGATURE OE �� LATIN SMALL LETTER O, LATIN SMALL LETTER E#
			{383, "f"},     // MA# ( ? �� f ) LATIN SMALL LETTER LONG S �� LATIN SMALL LETTER F#
			{385, "'B"},    // MA# ( ? �� 'B ) LATIN CAPITAL LETTER B WITH HOOK �� APOSTROPHE, LATIN CAPITAL LETTER B# ��?B��
			{388, "b"},     // MA# ( ? �� b ) LATIN CAPITAL LETTER TONE SIX �� LATIN SMALL LETTER B#
			{391, "C'"},    // MA# ( ? �� C' ) LATIN CAPITAL LETTER C WITH HOOK �� LATIN CAPITAL LETTER C, APOSTROPHE# ��C?��
			{394, "'D"},    // MA# ( ? �� 'D ) LATIN CAPITAL LETTER D WITH HOOK �� APOSTROPHE, LATIN CAPITAL LETTER D# ��?D��
			{397, "g"},     // MA# ( ? �� g ) LATIN SMALL LETTER TURNED DELTA �� LATIN SMALL LETTER G#
			{403, "G'"},    // MA# ( ? �� G' ) LATIN CAPITAL LETTER G WITH HOOK �� LATIN CAPITAL LETTER G, APOSTROPHE# ��G?��
			{406, "l"},     // MA# ( ? �� l ) LATIN CAPITAL LETTER IOTA �� LATIN SMALL LETTER L#
			{408, "K'"},    // MA# ( ? �� K' ) LATIN CAPITAL LETTER K WITH HOOK �� LATIN CAPITAL LETTER K, APOSTROPHE# ��K?��
			{416, "O'"},    // MA# ( ? �� O' ) LATIN CAPITAL LETTER O WITH HORN �� LATIN CAPITAL LETTER O, APOSTROPHE# ��O?��
			{417, "o'"},    // MA# ( ? �� o' ) LATIN SMALL LETTER O WITH HORN �� LATIN SMALL LETTER O, APOSTROPHE# ��o?��
			{420, "'P"},    // MA# ( ? �� 'P ) LATIN CAPITAL LETTER P WITH HOOK �� APOSTROPHE, LATIN CAPITAL LETTER P# ��?P��
			{422, "R"},     // MA# ( ? �� R ) LATIN LETTER YR �� LATIN CAPITAL LETTER R#
			{423, "2"},     // MA# ( ? �� 2 ) LATIN CAPITAL LETTER TONE TWO �� DIGIT TWO#
			{428, "'T"},    // MA# ( ? �� 'T ) LATIN CAPITAL LETTER T WITH HOOK �� APOSTROPHE, LATIN CAPITAL LETTER T# ��?T��
			{435, "'Y"},    // MA# ( ? �� 'Y ) LATIN CAPITAL LETTER Y WITH HOOK �� APOSTROPHE, LATIN CAPITAL LETTER Y# ��?Y��
			{439, "3"},     // MA# ( ? �� 3 ) LATIN CAPITAL LETTER EZH �� DIGIT THREE#
			{444, "5"},     // MA# ( ? �� 5 ) LATIN CAPITAL LETTER TONE FIVE �� DIGIT FIVE#
			{445, "s"},     // MA# ( ? �� s ) LATIN SMALL LETTER TONE FIVE �� LATIN SMALL LETTER S#
			{448, "l"},     // MA# ( ? �� l ) LATIN LETTER DENTAL CLICK �� LATIN SMALL LETTER L#
			{449, "ll"},    // MA# ( ? �� ll ) LATIN LETTER LATERAL CLICK �� LATIN SMALL LETTER L, LATIN SMALL LETTER L# ���������Ρ���||��
			{451, "!"},     // MA# ( ? �� ! ) LATIN LETTER RETROFLEX CLICK �� EXCLAMATION MARK#
			{455, "LJ"},    // MA# ( ? �� LJ ) LATIN CAPITAL LETTER LJ �� LATIN CAPITAL LETTER L, LATIN CAPITAL LETTER J#
			{456, "Lj"},    // MA# ( ? �� Lj ) LATIN CAPITAL LETTER L WITH SMALL LETTER J �� LATIN CAPITAL LETTER L, LATIN SMALL LETTER J#
			{457, "lj"},    // MA# ( ? �� lj ) LATIN SMALL LETTER LJ �� LATIN SMALL LETTER L, LATIN SMALL LETTER J#
			{458, "NJ"},    // MA# ( ? �� NJ ) LATIN CAPITAL LETTER NJ �� LATIN CAPITAL LETTER N, LATIN CAPITAL LETTER J#
			{459, "Nj"},    // MA# ( ? �� Nj ) LATIN CAPITAL LETTER N WITH SMALL LETTER J �� LATIN CAPITAL LETTER N, LATIN SMALL LETTER J#
			{460, "nj"},    // MA# ( ? �� nj ) LATIN SMALL LETTER NJ �� LATIN SMALL LETTER N, LATIN SMALL LETTER J#
			{497, "DZ"},    // MA# ( ? �� DZ ) LATIN CAPITAL LETTER DZ �� LATIN CAPITAL LETTER D, LATIN CAPITAL LETTER Z#
			{498, "Dz"},    // MA# ( ? �� Dz ) LATIN CAPITAL LETTER D WITH SMALL LETTER Z �� LATIN CAPITAL LETTER D, LATIN SMALL LETTER Z#
			{499, "dz"},    // MA# ( ? �� dz ) LATIN SMALL LETTER DZ �� LATIN SMALL LETTER D, LATIN SMALL LETTER Z#
			{540, "3"},     // MA# ( ? �� 3 ) LATIN CAPITAL LETTER YOGH �� DIGIT THREE# ��?��
			{546, "8"},     // MA# ( ? �� 8 ) LATIN CAPITAL LETTER OU �� DIGIT EIGHT#
			{547, "8"},     // MA# ( ? �� 8 ) LATIN SMALL LETTER OU �� DIGIT EIGHT#
			{577, "?"},     // MA# ( ? �� ? ) LATIN CAPITAL LETTER GLOTTAL STOP �� QUESTION MARK# ��?��
			{593, "a"},     // MA# ( �� �� a ) LATIN SMALL LETTER ALPHA �� LATIN SMALL LETTER A#
			{609, "g"},     // MA# ( �� �� g ) LATIN SMALL LETTER SCRIPT G �� LATIN SMALL LETTER G#
			{611, "y"},     // MA# ( ? �� y ) LATIN SMALL LETTER GAMMA �� LATIN SMALL LETTER Y# ���á�
			{617, "i"},     // MA# ( ? �� i ) LATIN SMALL LETTER IOTA �� LATIN SMALL LETTER I#
			{618, "i"},     // MA# ( ? �� i ) LATIN LETTER SMALL CAPITAL I �� LATIN SMALL LETTER I# ��?��
			{623, "w"},     // MA# ( ? �� w ) LATIN SMALL LETTER TURNED M �� LATIN SMALL LETTER W#
			{651, "u"},     // MA# ( ? �� u ) LATIN SMALL LETTER V WITH HOOK �� LATIN SMALL LETTER U#
			{655, "y"},     // MA# ( ? �� y ) LATIN LETTER SMALL CAPITAL Y �� LATIN SMALL LETTER Y# ��?�����á�
			{660, "?"},     // MA# ( ? �� ? ) LATIN LETTER GLOTTAL STOP �� QUESTION MARK#
			{675, "dz"},    // MA# ( ? �� dz ) LATIN SMALL LETTER DZ DIGRAPH �� LATIN SMALL LETTER D, LATIN SMALL LETTER Z#
			{678, "ts"},    // MA# ( ? �� ts ) LATIN SMALL LETTER TS DIGRAPH �� LATIN SMALL LETTER T, LATIN SMALL LETTER S#
			{682, "ls"},    // MA# ( ? �� ls ) LATIN SMALL LETTER LS DIGRAPH �� LATIN SMALL LETTER L, LATIN SMALL LETTER S#
			{683, "lz"},    // MA# ( ? �� lz ) LATIN SMALL LETTER LZ DIGRAPH �� LATIN SMALL LETTER L, LATIN SMALL LETTER Z#
			{697, "'"},     // MA# ( ? �� ' ) MODIFIER LETTER PRIME �� APOSTROPHE#
			{698, "\""},    // MA# ( ? �� '' ) MODIFIER LETTER DOUBLE PRIME �� APOSTROPHE, APOSTROPHE# ��"��# Converted to a quote.
			{699, "'"},     // MA# ( ? �� ' ) MODIFIER LETTER TURNED COMMA �� APOSTROPHE# ������
			{700, "'"},     // MA# ( ? �� ' ) MODIFIER LETTER APOSTROPHE �� APOSTROPHE# �����
			{701, "'"},     // MA# ( ? �� ' ) MODIFIER LETTER REVERSED COMMA �� APOSTROPHE# ������
			{702, "'"},     // MA# ( ? �� ' ) MODIFIER LETTER RIGHT HALF RING �� APOSTROPHE# ��?�������
			{706, "<"},     // MA#* ( ? �� < ) MODIFIER LETTER LEFT ARROWHEAD �� LESS-THAN SIGN#
			{707, ">"},     // MA#* ( ? �� > ) MODIFIER LETTER RIGHT ARROWHEAD �� GREATER-THAN SIGN#
			{708, "^"},     // MA#* ( ? �� ^ ) MODIFIER LETTER UP ARROWHEAD �� CIRCUMFLEX ACCENT#
			{710, "^"},     // MA# ( ? �� ^ ) MODIFIER LETTER CIRCUMFLEX ACCENT �� CIRCUMFLEX ACCENT#
			{712, "'"},     // MA# ( ? �� ' ) MODIFIER LETTER VERTICAL LINE �� APOSTROPHE#
			{714, "'"},     // MA# ( �@ �� ' ) MODIFIER LETTER ACUTE ACCENT �� APOSTROPHE# ��?�������
			{715, "'"},     // MA# ( �A �� ' ) MODIFIER LETTER GRAVE ACCENT �� APOSTROPHE# �����������
			{720, ":"},     // MA# ( ? �� : ) MODIFIER LETTER TRIANGULAR COLON �� COLON#
			{727, "-"},     // MA#* ( ? �� - ) MODIFIER LETTER MINUS SIGN �� HYPHEN-MINUS#
			{731, "i"},     // MA#* ( ? �� i ) OGONEK �� LATIN SMALL LETTER I# ��?����?�����ɡ�
			{732, "~"},     // MA#* ( ? �� ~ ) SMALL TILDE �� TILDE#
			{733, "\""},    // MA#* ( ? �� '' ) DOUBLE ACUTE ACCENT �� APOSTROPHE, APOSTROPHE# ��"��# Converted to a quote.
			{750, "\""},    // MA# ( ? �� '' ) MODIFIER LETTER DOUBLE APOSTROPHE �� APOSTROPHE, APOSTROPHE# �������"��# Converted to a quote.
			{756, "'"},     // MA#* ( ? �� ' ) MODIFIER LETTER MIDDLE GRAVE ACCENT �� APOSTROPHE# ���A�������������
			{758, "\""},    // MA#* ( ? �� '' ) MODIFIER LETTER MIDDLE DOUBLE ACUTE ACCENT �� APOSTROPHE, APOSTROPHE# ��?����"��# Converted to a quote.
			{760, ":"},     // MA#* ( ? �� : ) MODIFIER LETTER RAISED COLON �� COLON#
			{884, "'"},     // MA# ( ? �� ' ) GREEK NUMERAL SIGN �� APOSTROPHE# �����
			{890, "i"},     // MA#* ( ? �� i ) GREEK YPOGEGRAMMENI �� LATIN SMALL LETTER I# ��?�����ɡ�
			{894, ";"},     // MA#* ( ? �� ; ) GREEK QUESTION MARK �� SEMICOLON#
			{895, "J"},     // MA# ( ? �� J ) GREEK CAPITAL LETTER YOT �� LATIN CAPITAL LETTER J#
			{900, "'"},     // MA#* ( ? �� ' ) GREEK TONOS �� APOSTROPHE# ��?��
			{913, "A"},     // MA# ( �� �� A ) GREEK CAPITAL LETTER ALPHA �� LATIN CAPITAL LETTER A#
			{914, "B"},     // MA# ( �� �� B ) GREEK CAPITAL LETTER BETA �� LATIN CAPITAL LETTER B#
			{917, "E"},     // MA# ( �� �� E ) GREEK CAPITAL LETTER EPSILON �� LATIN CAPITAL LETTER E#
			{918, "Z"},     // MA# ( �� �� Z ) GREEK CAPITAL LETTER ZETA �� LATIN CAPITAL LETTER Z#
			{919, "H"},     // MA# ( �� �� H ) GREEK CAPITAL LETTER ETA �� LATIN CAPITAL LETTER H#
			{921, "l"},     // MA# ( �� �� l ) GREEK CAPITAL LETTER IOTA �� LATIN SMALL LETTER L#
			{922, "K"},     // MA# ( �� �� K ) GREEK CAPITAL LETTER KAPPA �� LATIN CAPITAL LETTER K#
			{924, "M"},     // MA# ( �� �� M ) GREEK CAPITAL LETTER MU �� LATIN CAPITAL LETTER M#
			{925, "N"},     // MA# ( �� �� N ) GREEK CAPITAL LETTER NU �� LATIN CAPITAL LETTER N#
			{927, "O"},     // MA# ( �� �� O ) GREEK CAPITAL LETTER OMICRON �� LATIN CAPITAL LETTER O#
			{929, "P"},     // MA# ( �� �� P ) GREEK CAPITAL LETTER RHO �� LATIN CAPITAL LETTER P#
			{932, "T"},     // MA# ( �� �� T ) GREEK CAPITAL LETTER TAU �� LATIN CAPITAL LETTER T#
			{933, "Y"},     // MA# ( �� �� Y ) GREEK CAPITAL LETTER UPSILON �� LATIN CAPITAL LETTER Y#
			{935, "X"},     // MA# ( �� �� X ) GREEK CAPITAL LETTER CHI �� LATIN CAPITAL LETTER X#
			{945, "a"},     // MA# ( �� �� a ) GREEK SMALL LETTER ALPHA �� LATIN SMALL LETTER A#
			{947, "y"},     // MA# ( �� �� y ) GREEK SMALL LETTER GAMMA �� LATIN SMALL LETTER Y#
			{953, "i"},     // MA# ( �� �� i ) GREEK SMALL LETTER IOTA �� LATIN SMALL LETTER I#
			{957, "v"},     // MA# ( �� �� v ) GREEK SMALL LETTER NU �� LATIN SMALL LETTER V#
			{959, "o"},     // MA# ( �� �� o ) GREEK SMALL LETTER OMICRON �� LATIN SMALL LETTER O#
			{961, "p"},     // MA# ( �� �� p ) GREEK SMALL LETTER RHO �� LATIN SMALL LETTER P#
			{963, "o"},     // MA# ( �� �� o ) GREEK SMALL LETTER SIGMA �� LATIN SMALL LETTER O#
			{965, "u"},     // MA# ( �� �� u ) GREEK SMALL LETTER UPSILON �� LATIN SMALL LETTER U# ��?��
			{978, "Y"},     // MA# ( ? �� Y ) GREEK UPSILON WITH HOOK SYMBOL �� LATIN CAPITAL LETTER Y#
			{988, "F"},     // MA# ( ? �� F ) GREEK LETTER DIGAMMA �� LATIN CAPITAL LETTER F#
			{1000, "2"},    // MA# ( ? �� 2 ) COPTIC CAPITAL LETTER HORI �� DIGIT TWO# ��?��
			{1009, "p"},    // MA# ( ? �� p ) GREEK RHO SYMBOL �� LATIN SMALL LETTER P# ���ѡ�
			{1010, "c"},    // MA# ( ? �� c ) GREEK LUNATE SIGMA SYMBOL �� LATIN SMALL LETTER C#
			{1011, "j"},    // MA# ( ? �� j ) GREEK LETTER YOT �� LATIN SMALL LETTER J#
			{1017, "C"},    // MA# ( ? �� C ) GREEK CAPITAL LUNATE SIGMA SYMBOL �� LATIN CAPITAL LETTER C#
			{1018, "M"},    // MA# ( ? �� M ) GREEK CAPITAL LETTER SAN �� LATIN CAPITAL LETTER M#
			{1029, "S"},    // MA# ( ? �� S ) CYRILLIC CAPITAL LETTER DZE �� LATIN CAPITAL LETTER S#
			{1030, "l"},    // MA# ( ? �� l ) CYRILLIC CAPITAL LETTER BYELORUSSIAN-UKRAINIAN I �� LATIN SMALL LETTER L#
			{1032, "J"},    // MA# ( ? �� J ) CYRILLIC CAPITAL LETTER JE �� LATIN CAPITAL LETTER J#
			{1040, "A"},    // MA# ( �� �� A ) CYRILLIC CAPITAL LETTER A �� LATIN CAPITAL LETTER A#
			{1042, "B"},    // MA# ( �� �� B ) CYRILLIC CAPITAL LETTER VE �� LATIN CAPITAL LETTER B#
			{1045, "E"},    // MA# ( �� �� E ) CYRILLIC CAPITAL LETTER IE �� LATIN CAPITAL LETTER E#
			{1047, "3"},    // MA# ( �� �� 3 ) CYRILLIC CAPITAL LETTER ZE �� DIGIT THREE#
			{1050, "K"},    // MA# ( �� �� K ) CYRILLIC CAPITAL LETTER KA �� LATIN CAPITAL LETTER K#
			{1052, "M"},    // MA# ( �� �� M ) CYRILLIC CAPITAL LETTER EM �� LATIN CAPITAL LETTER M#
			{1053, "H"},    // MA# ( �� �� H ) CYRILLIC CAPITAL LETTER EN �� LATIN CAPITAL LETTER H#
			{1054, "O"},    // MA# ( �� �� O ) CYRILLIC CAPITAL LETTER O �� LATIN CAPITAL LETTER O#
			{1056, "P"},    // MA# ( �� �� P ) CYRILLIC CAPITAL LETTER ER �� LATIN CAPITAL LETTER P#
			{1057, "C"},    // MA# ( �� �� C ) CYRILLIC CAPITAL LETTER ES �� LATIN CAPITAL LETTER C#
			{1058, "T"},    // MA# ( �� �� T ) CYRILLIC CAPITAL LETTER TE �� LATIN CAPITAL LETTER T#
			{1059, "Y"},    // MA# ( �� �� Y ) CYRILLIC CAPITAL LETTER U �� LATIN CAPITAL LETTER Y#
			{1061, "X"},    // MA# ( �� �� X ) CYRILLIC CAPITAL LETTER HA �� LATIN CAPITAL LETTER X#
			{1067, "bl"},   // MA# ( �� �� bl ) CYRILLIC CAPITAL LETTER YERU �� LATIN SMALL LETTER B, LATIN SMALL LETTER L# ����?������1��
			{1068, "b"},    // MA# ( �� �� b ) CYRILLIC CAPITAL LETTER SOFT SIGN �� LATIN SMALL LETTER B# ��?��
			{1070, "lO"},   // MA# ( �� �� lO ) CYRILLIC CAPITAL LETTER YU �� LATIN SMALL LETTER L, LATIN CAPITAL LETTER O# ��IO��
			{1072, "a"},    // MA# ( �� �� a ) CYRILLIC SMALL LETTER A �� LATIN SMALL LETTER A#
			{1073, "6"},    // MA# ( �� �� 6 ) CYRILLIC SMALL LETTER BE �� DIGIT SIX#
			{1075, "r"},    // MA# ( �� �� r ) CYRILLIC SMALL LETTER GHE �� LATIN SMALL LETTER R#
			{1077, "e"},    // MA# ( �� �� e ) CYRILLIC SMALL LETTER IE �� LATIN SMALL LETTER E#
			{1086, "o"},    // MA# ( �� �� o ) CYRILLIC SMALL LETTER O �� LATIN SMALL LETTER O#
			{1088, "p"},    // MA# ( �� �� p ) CYRILLIC SMALL LETTER ER �� LATIN SMALL LETTER P#
			{1089, "c"},    // MA# ( �� �� c ) CYRILLIC SMALL LETTER ES �� LATIN SMALL LETTER C#
			{1091, "y"},    // MA# ( �� �� y ) CYRILLIC SMALL LETTER U �� LATIN SMALL LETTER Y#
			{1093, "x"},    // MA# ( �� �� x ) CYRILLIC SMALL LETTER HA �� LATIN SMALL LETTER X#
			{1109, "s"},    // MA# ( ? �� s ) CYRILLIC SMALL LETTER DZE �� LATIN SMALL LETTER S#
			{1110, "i"},    // MA# ( ? �� i ) CYRILLIC SMALL LETTER BYELORUSSIAN-UKRAINIAN I �� LATIN SMALL LETTER I#
			{1112, "j"},    // MA# ( ? �� j ) CYRILLIC SMALL LETTER JE �� LATIN SMALL LETTER J#
			{1121, "w"},    // MA# ( ? �� w ) CYRILLIC SMALL LETTER OMEGA �� LATIN SMALL LETTER W#
			{1140, "V"},    // MA# ( ? �� V ) CYRILLIC CAPITAL LETTER IZHITSA �� LATIN CAPITAL LETTER V#
			{1141, "v"},    // MA# ( ? �� v ) CYRILLIC SMALL LETTER IZHITSA �� LATIN SMALL LETTER V#
			{1169, "r'"},   // MA# ( ? �� r' ) CYRILLIC SMALL LETTER GHE WITH UPTURN �� LATIN SMALL LETTER R, APOSTROPHE# ����?��
			{1198, "Y"},    // MA# ( ? �� Y ) CYRILLIC CAPITAL LETTER STRAIGHT U �� LATIN CAPITAL LETTER Y#
			{1199, "y"},    // MA# ( ? �� y ) CYRILLIC SMALL LETTER STRAIGHT U �� LATIN SMALL LETTER Y# ���á�
			{1211, "h"},    // MA# ( ? �� h ) CYRILLIC SMALL LETTER SHHA �� LATIN SMALL LETTER H#
			{1213, "e"},    // MA# ( ? �� e ) CYRILLIC SMALL LETTER ABKHASIAN CHE �� LATIN SMALL LETTER E#
			{1216, "l"},    // MA# ( ? �� l ) CYRILLIC LETTER PALOCHKA �� LATIN SMALL LETTER L#
			{1231, "i"},    // MA# ( ? �� i ) CYRILLIC SMALL LETTER PALOCHKA �� LATIN SMALL LETTER I# ��?��
			{1236, "AE"},   // MA# ( ? �� AE ) CYRILLIC CAPITAL LIGATURE A IE �� LATIN CAPITAL LETTER A, LATIN CAPITAL LETTER E# ��?��
			{1237, "ae"},   // MA# ( ? �� ae ) CYRILLIC SMALL LIGATURE A IE �� LATIN SMALL LETTER A, LATIN SMALL LETTER E# ���ѧ֡�
			{1248, "3"},    // MA# ( ? �� 3 ) CYRILLIC CAPITAL LETTER ABKHASIAN DZE �� DIGIT THREE# ��?��
			{1281, "d"},    // MA# ( ? �� d ) CYRILLIC SMALL LETTER KOMI DE �� LATIN SMALL LETTER D#
			{1292, "G"},    // MA# ( ? �� G ) CYRILLIC CAPITAL LETTER KOMI SJE �� LATIN CAPITAL LETTER G#
			{1307, "q"},    // MA# ( ? �� q ) CYRILLIC SMALL LETTER QA �� LATIN SMALL LETTER Q#
			{1308, "W"},    // MA# ( ? �� W ) CYRILLIC CAPITAL LETTER WE �� LATIN CAPITAL LETTER W#
			{1309, "w"},    // MA# ( ? �� w ) CYRILLIC SMALL LETTER WE �� LATIN SMALL LETTER W#
			{1357, "U"},    // MA# ( ? �� U ) ARMENIAN CAPITAL LETTER SEH �� LATIN CAPITAL LETTER U#
			{1359, "S"},    // MA# ( ? �� S ) ARMENIAN CAPITAL LETTER TIWN �� LATIN CAPITAL LETTER S#
			{1365, "O"},    // MA# ( ? �� O ) ARMENIAN CAPITAL LETTER OH �� LATIN CAPITAL LETTER O#
			{1370, "'"},    // MA#* ( ? �� ' ) ARMENIAN APOSTROPHE �� APOSTROPHE# ������
			{1373, "'"},    // MA#* ( ? �� ' ) ARMENIAN COMMA �� APOSTROPHE# ���A�������������
			{1377, "w"},    // MA# ( ? �� w ) ARMENIAN SMALL LETTER AYB �� LATIN SMALL LETTER W# ��?��
			{1379, "q"},    // MA# ( ? �� q ) ARMENIAN SMALL LETTER GIM �� LATIN SMALL LETTER Q#
			{1382, "q"},    // MA# ( ? �� q ) ARMENIAN SMALL LETTER ZA �� LATIN SMALL LETTER Q#
			{1392, "h"},    // MA# ( ? �� h ) ARMENIAN SMALL LETTER HO �� LATIN SMALL LETTER H#
			{1400, "n"},    // MA# ( ? �� n ) ARMENIAN SMALL LETTER VO �� LATIN SMALL LETTER N#
			{1404, "n"},    // MA# ( ? �� n ) ARMENIAN SMALL LETTER RA �� LATIN SMALL LETTER N#
			{1405, "u"},    // MA# ( ? �� u ) ARMENIAN SMALL LETTER SEH �� LATIN SMALL LETTER U#
			{1409, "g"},    // MA# ( ? �� g ) ARMENIAN SMALL LETTER CO �� LATIN SMALL LETTER G#
			{1412, "f"},    // MA# ( ? �� f ) ARMENIAN SMALL LETTER KEH �� LATIN SMALL LETTER F#
			{1413, "o"},    // MA# ( ? �� o ) ARMENIAN SMALL LETTER OH �� LATIN SMALL LETTER O#
			{1417, ":"},    // MA#* ( ? �� : ) ARMENIAN FULL STOP �� COLON#
			{1472, "l"},    // MA#* ( ??? �� l ) HEBREW PUNCTUATION PASEQ �� LATIN SMALL LETTER L# ��|��
			{1475, ":"},    // MA#* ( ??? �� : ) HEBREW PUNCTUATION SOF PASUQ �� COLON#
			{1493, "l"},    // MA# ( ??? �� l ) HEBREW LETTER VAV �� LATIN SMALL LETTER L#
			{1496, "v"},    // MA# ( ??? �� v ) HEBREW LETTER TET �� LATIN SMALL LETTER V#
			{1497, "'"},    // MA# ( ??? �� ' ) HEBREW LETTER YOD �� APOSTROPHE#
			{1503, "l"},    // MA# ( ??? �� l ) HEBREW LETTER FINAL NUN �� LATIN SMALL LETTER L#
			{1505, "o"},    // MA# ( ??? �� o ) HEBREW LETTER SAMEKH �� LATIN SMALL LETTER O#
			{1520, "ll"},   // MA# ( ??? �� ll ) HEBREW LIGATURE YIDDISH DOUBLE VAV �� LATIN SMALL LETTER L, LATIN SMALL LETTER L# ��????��
			{1521, "l'"},   // MA# ( ??? �� l' ) HEBREW LIGATURE YIDDISH VAV YOD �� LATIN SMALL LETTER L, APOSTROPHE# ��????��
			{1522, "\""},   // MA# ( ??? �� '' ) HEBREW LIGATURE YIDDISH DOUBLE YOD �� APOSTROPHE, APOSTROPHE# ��????��# Converted to a quote.
			{1523, "'"},    // MA#* ( ??? �� ' ) HEBREW PUNCTUATION GERESH �� APOSTROPHE#
			{1524, "\""},   // MA#* ( ??? �� '' ) HEBREW PUNCTUATION GERSHAYIM �� APOSTROPHE, APOSTROPHE# ��"��# Converted to a quote.
			{1549, ","},    // MA#* ( ??? �� , ) ARABIC DATE SEPARATOR �� COMMA# ��???��
			{1575, "l"},    // MA# ( ??? �� l ) ARABIC LETTER ALEF �� LATIN SMALL LETTER L# ��1��
			{1607, "o"},    // MA# ( ??? �� o ) ARABIC LETTER HEH �� LATIN SMALL LETTER O#
			{1632, "."},    // MA# ( ??? �� . ) ARABIC-INDIC DIGIT ZERO �� FULL STOP#
			{1633, "l"},    // MA# ( ??? �� l ) ARABIC-INDIC DIGIT ONE �� LATIN SMALL LETTER L# ��1��
			{1637, "o"},    // MA# ( ??? �� o ) ARABIC-INDIC DIGIT FIVE �� LATIN SMALL LETTER O#
			{1639, "V"},    // MA# ( ??? �� V ) ARABIC-INDIC DIGIT SEVEN �� LATIN CAPITAL LETTER V#
			{1643, ","},    // MA#* ( ??? �� , ) ARABIC DECIMAL SEPARATOR �� COMMA#
			{1645, "*"},    // MA#* ( ??? �� * ) ARABIC FIVE POINTED STAR �� ASTERISK#
			{1726, "o"},    // MA# ( ??? �� o ) ARABIC LETTER HEH DOACHASHMEE �� LATIN SMALL LETTER O# ��???��
			{1729, "o"},    // MA# ( ??? �� o ) ARABIC LETTER HEH GOAL �� LATIN SMALL LETTER O# ��???��
			{1748, "-"},    // MA#* ( ??? �� - ) ARABIC FULL STOP �� HYPHEN-MINUS# ���\��
			{1749, "o"},    // MA# ( ??? �� o ) ARABIC LETTER AE �� LATIN SMALL LETTER O# ��???��
			{1776, "."},    // MA# ( ? �� . ) EXTENDED ARABIC-INDIC DIGIT ZERO �� FULL STOP# ��???��
			{1777, "l"},    // MA# ( ? �� l ) EXTENDED ARABIC-INDIC DIGIT ONE �� LATIN SMALL LETTER L# ��1��
			{1781, "o"},    // MA# ( ? �� o ) EXTENDED ARABIC-INDIC DIGIT FIVE �� LATIN SMALL LETTER O# ��???��
			{1783, "V"},    // MA# ( ? �� V ) EXTENDED ARABIC-INDIC DIGIT SEVEN �� LATIN CAPITAL LETTER V# ��???��
			{1793, "."},    // MA#* ( ??? �� . ) SYRIAC SUPRALINEAR FULL STOP �� FULL STOP#
			{1794, "."},    // MA#* ( ??? �� . ) SYRIAC SUBLINEAR FULL STOP �� FULL STOP#
			{1795, ":"},    // MA#* ( ??? �� : ) SYRIAC SUPRALINEAR COLON �� COLON#
			{1796, ":"},    // MA#* ( ??? �� : ) SYRIAC SUBLINEAR COLON �� COLON#
			{1984, "O"},    // MA# ( ??? �� O ) NKO DIGIT ZERO �� LATIN CAPITAL LETTER O# ��0��
			{1994, "l"},    // MA# ( ??? �� l ) NKO LETTER A �� LATIN SMALL LETTER L# ���O����?��
			{2036, "'"},    // MA# ( ??? �� ' ) NKO HIGH TONE APOSTROPHE �� APOSTROPHE# ������
			{2037, "'"},    // MA# ( ??? �� ' ) NKO LOW TONE APOSTROPHE �� APOSTROPHE# ������
			{2042, "_"},    // MA# ( ??? �� _ ) NKO LAJANYALAN �� LOW LINE#
			{2307, ":"},    // MA# ( ? �� : ) DEVANAGARI SIGN VISARGA �� COLON#
			{2406, "o"},    // MA# ( ? �� o ) DEVANAGARI DIGIT ZERO �� LATIN SMALL LETTER O#
			{2429, "?"},    // MA# ( ? �� ? ) DEVANAGARI LETTER GLOTTAL STOP �� QUESTION MARK#
			{2534, "O"},    // MA# ( ? �� O ) BENGALI DIGIT ZERO �� LATIN CAPITAL LETTER O# ��0��
			{2538, "8"},    // MA# ( ? �� 8 ) BENGALI DIGIT FOUR �� DIGIT EIGHT#
			{2541, "9"},    // MA# ( ? �� 9 ) BENGALI DIGIT SEVEN �� DIGIT NINE#
			{2662, "o"},    // MA# ( ? �� o ) GURMUKHI DIGIT ZERO �� LATIN SMALL LETTER O#
			{2663, "9"},    // MA# ( ? �� 9 ) GURMUKHI DIGIT ONE �� DIGIT NINE#
			{2666, "8"},    // MA# ( ? �� 8 ) GURMUKHI DIGIT FOUR �� DIGIT EIGHT#
			{2691, ":"},    // MA# ( ? �� : ) GUJARATI SIGN VISARGA �� COLON#
			{2790, "o"},    // MA# ( ? �� o ) GUJARATI DIGIT ZERO �� LATIN SMALL LETTER O#
			{2819, "8"},    // MA# ( ? �� 8 ) ORIYA SIGN VISARGA �� DIGIT EIGHT#
			{2848, "O"},    // MA# ( ? �� O ) ORIYA LETTER TTHA �� LATIN CAPITAL LETTER O# ��?����0��
			{2918, "O"},    // MA# ( ? �� O ) ORIYA DIGIT ZERO �� LATIN CAPITAL LETTER O# ��0��
			{2920, "9"},    // MA# ( ? �� 9 ) ORIYA DIGIT TWO �� DIGIT NINE#
			{3046, "o"},    // MA# ( ? �� o ) TAMIL DIGIT ZERO �� LATIN SMALL LETTER O#
			{3074, "o"},    // MA# ( ? �� o ) TELUGU SIGN ANUSVARA �� LATIN SMALL LETTER O#
			{3174, "o"},    // MA# ( ? �� o ) TELUGU DIGIT ZERO �� LATIN SMALL LETTER O#
			{3202, "o"},    // MA# ( ? �� o ) KANNADA SIGN ANUSVARA �� LATIN SMALL LETTER O#
			{3302, "o"},    // MA# ( ? �� o ) KANNADA DIGIT ZERO �� LATIN SMALL LETTER O# ��?��
			{3330, "o"},    // MA# ( ? �� o ) MALAYALAM SIGN ANUSVARA �� LATIN SMALL LETTER O#
			{3360, "o"},    // MA# ( ? �� o ) MALAYALAM LETTER TTHA �� LATIN SMALL LETTER O#
			{3430, "o"},    // MA# ( ? �� o ) MALAYALAM DIGIT ZERO �� LATIN SMALL LETTER O#
			{3437, "9"},    // MA# ( ? �� 9 ) MALAYALAM DIGIT SEVEN �� DIGIT NINE#
			{3458, "o"},    // MA# ( ? �� o ) SINHALA SIGN ANUSVARAYA �� LATIN SMALL LETTER O#
			{3664, "o"},    // MA# ( ? �� o ) THAI DIGIT ZERO �� LATIN SMALL LETTER O#
			{3792, "o"},    // MA# ( ? �� o ) LAO DIGIT ZERO �� LATIN SMALL LETTER O#
			{4125, "o"},    // MA# ( ? �� o ) MYANMAR LETTER WA �� LATIN SMALL LETTER O#
			{4160, "o"},    // MA# ( ? �� o ) MYANMAR DIGIT ZERO �� LATIN SMALL LETTER O#
			{4327, "y"},    // MA# ( ? �� y ) GEORGIAN LETTER QAR �� LATIN SMALL LETTER Y#
			{4351, "o"},    // MA# ( ? �� o ) GEORGIAN LETTER LABIAL SIGN �� LATIN SMALL LETTER O#
			{4608, "U"},    // MA# ( ? �� U ) ETHIOPIC SYLLABLE HA �� LATIN CAPITAL LETTER U# ��?��
			{4816, "O"},    // MA# ( ? �� O ) ETHIOPIC SYLLABLE PHARYNGEAL A �� LATIN CAPITAL LETTER O# ��?��
			{5024, "D"},    // MA# ( ? �� D ) CHEROKEE LETTER A �� LATIN CAPITAL LETTER D#
			{5025, "R"},    // MA# ( ? �� R ) CHEROKEE LETTER E �� LATIN CAPITAL LETTER R#
			{5026, "T"},    // MA# ( ? �� T ) CHEROKEE LETTER I �� LATIN CAPITAL LETTER T#
			{5028, "O'"},   // MA# ( ? �� O' ) CHEROKEE LETTER U �� LATIN CAPITAL LETTER O, APOSTROPHE# ��?����O?��
			{5029, "i"},    // MA# ( ? �� i ) CHEROKEE LETTER V �� LATIN SMALL LETTER I#
			{5033, "Y"},    // MA# ( ? �� Y ) CHEROKEE LETTER GI �� LATIN CAPITAL LETTER Y#
			{5034, "A"},    // MA# ( ? �� A ) CHEROKEE LETTER GO �� LATIN CAPITAL LETTER A#
			{5035, "J"},    // MA# ( ? �� J ) CHEROKEE LETTER GU �� LATIN CAPITAL LETTER J#
			{5036, "E"},    // MA# ( ? �� E ) CHEROKEE LETTER GV �� LATIN CAPITAL LETTER E#
			{5038, "?"},    // MA# ( ? �� ? ) CHEROKEE LETTER HE �� QUESTION MARK# ��?����?��
			{5043, "W"},    // MA# ( ? �� W ) CHEROKEE LETTER LA �� LATIN CAPITAL LETTER W#
			{5047, "M"},    // MA# ( ? �� M ) CHEROKEE LETTER LU �� LATIN CAPITAL LETTER M#
			{5051, "H"},    // MA# ( ? �� H ) CHEROKEE LETTER MI �� LATIN CAPITAL LETTER H#
			{5053, "Y"},    // MA# ( ? �� Y ) CHEROKEE LETTER MU �� LATIN CAPITAL LETTER Y# ��?��
			{5056, "G"},    // MA# ( ? �� G ) CHEROKEE LETTER NAH �� LATIN CAPITAL LETTER G#
			{5058, "h"},    // MA# ( ? �� h ) CHEROKEE LETTER NI �� LATIN SMALL LETTER H#
			{5059, "Z"},    // MA# ( ? �� Z ) CHEROKEE LETTER NO �� LATIN CAPITAL LETTER Z#
			{5070, "4"},    // MA# ( ? �� 4 ) CHEROKEE LETTER SE �� DIGIT FOUR#
			{5071, "b"},    // MA# ( ? �� b ) CHEROKEE LETTER SI �� LATIN SMALL LETTER B#
			{5074, "R"},    // MA# ( ? �� R ) CHEROKEE LETTER SV �� LATIN CAPITAL LETTER R#
			{5076, "W"},    // MA# ( ? �� W ) CHEROKEE LETTER TA �� LATIN CAPITAL LETTER W#
			{5077, "S"},    // MA# ( ? �� S ) CHEROKEE LETTER DE �� LATIN CAPITAL LETTER S#
			{5081, "V"},    // MA# ( ? �� V ) CHEROKEE LETTER DO �� LATIN CAPITAL LETTER V#
			{5082, "S"},    // MA# ( ? �� S ) CHEROKEE LETTER DU �� LATIN CAPITAL LETTER S#
			{5086, "L"},    // MA# ( ? �� L ) CHEROKEE LETTER TLE �� LATIN CAPITAL LETTER L#
			{5087, "C"},    // MA# ( ? �� C ) CHEROKEE LETTER TLI �� LATIN CAPITAL LETTER C#
			{5090, "P"},    // MA# ( ? �� P ) CHEROKEE LETTER TLV �� LATIN CAPITAL LETTER P#
			{5094, "K"},    // MA# ( ? �� K ) CHEROKEE LETTER TSO �� LATIN CAPITAL LETTER K#
			{5095, "d"},    // MA# ( ? �� d ) CHEROKEE LETTER TSU �� LATIN SMALL LETTER D#
			{5102, "6"},    // MA# ( ? �� 6 ) CHEROKEE LETTER WV �� DIGIT SIX#
			{5107, "G"},    // MA# ( ? �� G ) CHEROKEE LETTER YU �� LATIN CAPITAL LETTER G#
			{5108, "B"},    // MA# ( ? �� B ) CHEROKEE LETTER YV �� LATIN CAPITAL LETTER B#
			{5120, "="},    // MA#* ( ? �� = ) CANADIAN SYLLABICS HYPHEN �� EQUALS SIGN#
			{5167, "V"},    // MA# ( ? �� V ) CANADIAN SYLLABICS PE �� LATIN CAPITAL LETTER V#
			{5171, ">"},    // MA# ( ? �� > ) CANADIAN SYLLABICS PO �� GREATER-THAN SIGN#
			{5176, "<"},    // MA# ( ? �� < ) CANADIAN SYLLABICS PA �� LESS-THAN SIGN#
			{5194, "'"},    // MA# ( ? �� ' ) CANADIAN SYLLABICS WEST-CREE P �� APOSTROPHE# ��?��
			{5196, "U"},    // MA# ( ? �� U ) CANADIAN SYLLABICS TE �� LATIN CAPITAL LETTER U#
			{5223, "U'"},   // MA# ( ? �� U' ) CANADIAN SYLLABICS TTE �� LATIN CAPITAL LETTER U, APOSTROPHE# ��??����?'��
			{5229, "P"},    // MA# ( ? �� P ) CANADIAN SYLLABICS KI �� LATIN CAPITAL LETTER P#
			{5231, "d"},    // MA# ( ? �� d ) CANADIAN SYLLABICS KO �� LATIN SMALL LETTER D#
			{5254, "P'"},   // MA# ( ? �� P' ) CANADIAN SYLLABICS SOUTH-SLAVEY KIH �� LATIN CAPITAL LETTER P, APOSTROPHE# ��??��
			{5255, "d'"},   // MA# ( ? �� d' ) CANADIAN SYLLABICS SOUTH-SLAVEY KOH �� LATIN SMALL LETTER D, APOSTROPHE# ��??��
			{5261, "J"},    // MA# ( ? �� J ) CANADIAN SYLLABICS CO �� LATIN CAPITAL LETTER J#
			{5290, "L"},    // MA# ( ? �� L ) CANADIAN SYLLABICS MA �� LATIN CAPITAL LETTER L#
			{5311, "2"},    // MA# ( ? �� 2 ) CANADIAN SYLLABICS SAYISI M �� DIGIT TWO#
			{5441, "x"},    // MA# ( ? �� x ) CANADIAN SYLLABICS SAYISI YI �� LATIN SMALL LETTER X# ��?��
			{5500, "H"},    // MA# ( ? �� H ) CANADIAN SYLLABICS NUNAVUT H �� LATIN CAPITAL LETTER H#
			{5501, "x"},    // MA# ( ? �� x ) CANADIAN SYLLABICS HK �� LATIN SMALL LETTER X# ��?����?��
			{5511, "R"},    // MA# ( ? �� R ) CANADIAN SYLLABICS TLHI �� LATIN CAPITAL LETTER R#
			{5551, "b"},    // MA# ( ? �� b ) CANADIAN SYLLABICS AIVILIK B �� LATIN SMALL LETTER B#
			{5556, "F"},    // MA# ( ? �� F ) CANADIAN SYLLABICS BLACKFOOT WE �� LATIN CAPITAL LETTER F#
			{5573, "A"},    // MA# ( ? �� A ) CANADIAN SYLLABICS CARRIER GHO �� LATIN CAPITAL LETTER A#
			{5598, "D"},    // MA# ( ? �� D ) CANADIAN SYLLABICS CARRIER THE �� LATIN CAPITAL LETTER D#
			{5610, "D"},    // MA# ( ? �� D ) CANADIAN SYLLABICS CARRIER PE �� LATIN CAPITAL LETTER D# ��?��
			{5616, "M"},    // MA# ( ? �� M ) CANADIAN SYLLABICS CARRIER GO �� LATIN CAPITAL LETTER M#
			{5623, "B"},    // MA# ( ? �� B ) CANADIAN SYLLABICS CARRIER KHE �� LATIN CAPITAL LETTER B#
			{5741, "X"},    // MA#* ( ? �� X ) CANADIAN SYLLABICS CHI SIGN �� LATIN CAPITAL LETTER X#
			{5742, "x"},    // MA#* ( ? �� x ) CANADIAN SYLLABICS FULL STOP �� LATIN SMALL LETTER X#
			{5760, " "},    // MA#* ( ? ��   ) OGHAM SPACE MARK �� SPACE#
			{5810, "<"},    // MA# ( ? �� < ) RUNIC LETTER KAUNA �� LESS-THAN SIGN#
			{5815, "X"},    // MA# ( ? �� X ) RUNIC LETTER GEBO GYFU G �� LATIN CAPITAL LETTER X#
			{5825, "l"},    // MA# ( ? �� l ) RUNIC LETTER ISAZ IS ISS I �� LATIN SMALL LETTER L# ��I��
			{5836, "'"},    // MA# ( ? �� ' ) RUNIC LETTER SHORT-TWIG-SOL S �� APOSTROPHE#
			{5845, "K"},    // MA# ( ? �� K ) RUNIC LETTER OPEN-P �� LATIN CAPITAL LETTER K#
			{5846, "M"},    // MA# ( ? �� M ) RUNIC LETTER EHWAZ EH E �� LATIN CAPITAL LETTER M#
			{5868, ":"},    // MA#* ( ? �� : ) RUNIC MULTIPLE PUNCTUATION �� COLON#
			{5869, "+"},    // MA#* ( ? �� + ) RUNIC CROSS PUNCTUATION �� PLUS SIGN#
			{5941, "/"},    // MA#* ( ? �� / ) PHILIPPINE SINGLE PUNCTUATION �� SOLIDUS#
			{6147, ":"},    // MA#* ( ? �� : ) MONGOLIAN FULL STOP �� COLON#
			{6153, ":"},    // MA#* ( ? �� : ) MONGOLIAN MANCHU FULL STOP �� COLON#
			{7379, "\""},   // MA#* ( ? �� '' ) VEDIC SIGN NIHSHVASA �� APOSTROPHE, APOSTROPHE# �������"��# Converted to a quote.
			{7428, "c"},    // MA# ( ? �� c ) LATIN LETTER SMALL CAPITAL C �� LATIN SMALL LETTER C#
			{7439, "o"},    // MA# ( ? �� o ) LATIN LETTER SMALL CAPITAL O �� LATIN SMALL LETTER O#
			{7441, "o"},    // MA# ( ? �� o ) LATIN SMALL LETTER SIDEWAYS O �� LATIN SMALL LETTER O#
			{7452, "u"},    // MA# ( ? �� u ) LATIN LETTER SMALL CAPITAL U �� LATIN SMALL LETTER U#
			{7456, "v"},    // MA# ( ? �� v ) LATIN LETTER SMALL CAPITAL V �� LATIN SMALL LETTER V#
			{7457, "w"},    // MA# ( ? �� w ) LATIN LETTER SMALL CAPITAL W �� LATIN SMALL LETTER W#
			{7458, "z"},    // MA# ( ? �� z ) LATIN LETTER SMALL CAPITAL Z �� LATIN SMALL LETTER Z#
			{7462, "r"},    // MA# ( ? �� r ) GREEK LETTER SMALL CAPITAL GAMMA �� LATIN SMALL LETTER R# ���ԡ�
			{7531, "ue"},   // MA# ( ? �� ue ) LATIN SMALL LETTER UE �� LATIN SMALL LETTER U, LATIN SMALL LETTER E#
			{7555, "g"},    // MA# ( ? �� g ) LATIN SMALL LETTER G WITH PALATAL HOOK �� LATIN SMALL LETTER G#
			{7564, "y"},    // MA# ( ? �� y ) LATIN SMALL LETTER V WITH PALATAL HOOK �� LATIN SMALL LETTER Y#
			{7837, "f"},    // MA# ( ? �� f ) LATIN SMALL LETTER LONG S WITH HIGH STROKE �� LATIN SMALL LETTER F#
			{7935, "y"},    // MA# ( ? �� y ) LATIN SMALL LETTER Y WITH LOOP �� LATIN SMALL LETTER Y#
			{8125, "'"},    // MA#* ( ? �� ' ) GREEK KORONIS �� APOSTROPHE# ������
			{8126, "i"},    // MA# ( ? �� i ) GREEK PROSGEGRAMMENI �� LATIN SMALL LETTER I# ���ɡ�
			{8127, "'"},    // MA#* ( ? �� ' ) GREEK PSILI �� APOSTROPHE# ������
			{8128, "~"},    // MA#* ( ? �� ~ ) GREEK PERISPOMENI �� TILDE# ��?��
			{8175, "'"},    // MA#* ( ? �� ' ) GREEK VARIA �� APOSTROPHE# ���A�������������
			{8189, "'"},    // MA#* ( ? �� ' ) GREEK OXIA �� APOSTROPHE# ��?����?����?��
			{8190, "'"},    // MA#* ( ? �� ' ) GREEK DASIA �� APOSTROPHE# ��?�������
			{8192, " "},    // MA#* ( ? ��   ) EN QUAD �� SPACE#
			{8193, " "},    // MA#* ( ? ��   ) EM QUAD �� SPACE#
			{8194, " "},    // MA#* ( ? ��   ) EN SPACE �� SPACE#
			{8195, " "},    // MA#* ( ? ��   ) EM SPACE �� SPACE#
			{8196, " "},    // MA#* ( ? ��   ) THREE-PER-EM SPACE �� SPACE#
			{8197, " "},    // MA#* ( ? ��   ) FOUR-PER-EM SPACE �� SPACE#
			{8198, " "},    // MA#* ( ? ��   ) SIX-PER-EM SPACE �� SPACE#
			{8199, " "},    // MA#* ( ? ��   ) FIGURE SPACE �� SPACE#
			{8200, " "},    // MA#* ( ? ��   ) PUNCTUATION SPACE �� SPACE#
			{8201, " "},    // MA#* ( ? ��   ) THIN SPACE �� SPACE#
			{8202, " "},    // MA#* ( ? ��   ) HAIR SPACE �� SPACE#
			{8208, "-"},    // MA#* ( �\ �� - ) HYPHEN �� HYPHEN-MINUS#
			{8209, "-"},    // MA#* ( ? �� - ) NON-BREAKING HYPHEN �� HYPHEN-MINUS#
			{8210, "-"},    // MA#* ( ? �� - ) FIGURE DASH �� HYPHEN-MINUS#
			{8211, "-"},    // MA#* ( �C �� - ) EN DASH �� HYPHEN-MINUS#
			{8214, "ll"},   // MA#* ( �� �� ll ) DOUBLE VERTICAL LINE �� LATIN SMALL LETTER L, LATIN SMALL LETTER L# ���Ρ���||��
			{8216, "'"},    // MA#* ( �� �� ' ) LEFT SINGLE QUOTATION MARK �� APOSTROPHE#
			{8217, "'"},    // MA#* ( �� �� ' ) RIGHT SINGLE QUOTATION MARK �� APOSTROPHE#
			{8218, ","},    // MA#* ( ? �� , ) SINGLE LOW-9 QUOTATION MARK �� COMMA#
			{8219, "'"},    // MA#* ( ? �� ' ) SINGLE HIGH-REVERSED-9 QUOTATION MARK �� APOSTROPHE# �����
			{8220, "\""},   // MA#* ( �� �� '' ) LEFT DOUBLE QUOTATION MARK �� APOSTROPHE, APOSTROPHE# ��"��# Converted to a quote.
			{8221, "\""},   // MA#* ( �� �� '' ) RIGHT DOUBLE QUOTATION MARK �� APOSTROPHE, APOSTROPHE# ��"��# Converted to a quote.
			{8223, "\""},   // MA#* ( ? �� '' ) DOUBLE HIGH-REVERSED-9 QUOTATION MARK �� APOSTROPHE, APOSTROPHE# ��������"��# Converted to a quote.
			{8228, "."},    // MA#* ( ? �� . ) ONE DOT LEADER �� FULL STOP#
			{8229, ".."},   // MA#* ( �E �� .. ) TWO DOT LEADER �� FULL STOP, FULL STOP#
			{8230, "..."},  // MA#* ( �� �� ... ) HORIZONTAL ELLIPSIS �� FULL STOP, FULL STOP, FULL STOP#
			{8232, " "},    // MA#* (  ��   ) LINE SEPARATOR �� SPACE#
			{8233, " "},    // MA#* (  ��   ) PARAGRAPH SEPARATOR �� SPACE#
			{8239, " "},    // MA#* ( ? ��   ) NARROW NO-BREAK SPACE �� SPACE#
			{8242, "'"},    // MA#* ( �� �� ' ) PRIME �� APOSTROPHE#
			{8243, "\""},   // MA#* ( �� �� '' ) DOUBLE PRIME �� APOSTROPHE, APOSTROPHE# ��"��# Converted to a quote.
			{8244, "'''"},  // MA#* ( ? �� ''' ) TRIPLE PRIME �� APOSTROPHE, APOSTROPHE, APOSTROPHE# �������
			{8245, "'"},    // MA#* ( �F �� ' ) REVERSED PRIME �� APOSTROPHE# ��?��������
			{8246, "\""},   // MA#* ( ? �� '' ) REVERSED DOUBLE PRIME �� APOSTROPHE, APOSTROPHE# ���F�F��# Converted to a quote.
			{8247, "'''"},  // MA#* ( ? �� ''' ) REVERSED TRIPLE PRIME �� APOSTROPHE, APOSTROPHE, APOSTROPHE# ���F�F�F��
			{8249, "<"},    // MA#* ( ? �� < ) SINGLE LEFT-POINTING ANGLE QUOTATION MARK �� LESS-THAN SIGN#
			{8250, ">"},    // MA#* ( ? �� > ) SINGLE RIGHT-POINTING ANGLE QUOTATION MARK �� GREATER-THAN SIGN#
			{8252, "!!"},   // MA#* ( ? �� !! ) DOUBLE EXCLAMATION MARK �� EXCLAMATION MARK, EXCLAMATION MARK#
			{8257, "/"},    // MA#* ( ? �� / ) CARET INSERTION POINT �� SOLIDUS#
			{8259, "-"},    // MA#* ( ? �� - ) HYPHEN BULLET �� HYPHEN-MINUS# ���\��
			{8260, "/"},    // MA#* ( ? �� / ) FRACTION SLASH �� SOLIDUS#
			{8263, "??"},   // MA#* ( ? �� ?? ) DOUBLE QUESTION MARK �� QUESTION MARK, QUESTION MARK#
			{8264, "?!"},   // MA#* ( ? �� ?! ) QUESTION EXCLAMATION MARK �� QUESTION MARK, EXCLAMATION MARK#
			{8265, "!?"},   // MA#* ( ? �� !? ) EXCLAMATION QUESTION MARK �� EXCLAMATION MARK, QUESTION MARK#
			{8270, "*"},    // MA#* ( ? �� * ) LOW ASTERISK �� ASTERISK#
			{8275, "~"},    // MA#* ( ? �� ~ ) SWUNG DASH �� TILDE#
			{8279, "''''"}, // MA#* ( ? �� '''' ) QUADRUPLE PRIME �� APOSTROPHE, APOSTROPHE, APOSTROPHE, APOSTROPHE# ��������
			{8282, ":"},    // MA#* ( ? �� : ) TWO DOT PUNCTUATION �� COLON#
			{8287, " "},    // MA#* ( ? ��   ) MEDIUM MATHEMATICAL SPACE �� SPACE#
			{8360, "Rs"},   // MA#* ( ? �� Rs ) RUPEE SIGN �� LATIN CAPITAL LETTER R, LATIN SMALL LETTER S#
			{8374, "lt"},   // MA#* ( ? �� lt ) LIVRE TOURNOIS SIGN �� LATIN SMALL LETTER L, LATIN SMALL LETTER T#
			{8448, "a/c"},  // MA#* ( ? �� a/c ) ACCOUNT OF �� LATIN SMALL LETTER A, SOLIDUS, LATIN SMALL LETTER C#
			{8449, "a/s"},  // MA#* ( ? �� a/s ) ADDRESSED TO THE SUBJECT �� LATIN SMALL LETTER A, SOLIDUS, LATIN SMALL LETTER S#
			{8450, "C"},    // MA# ( ? �� C ) DOUBLE-STRUCK CAPITAL C �� LATIN CAPITAL LETTER C#
			{8453, "c/o"},  // MA#* ( �G �� c/o ) CARE OF �� LATIN SMALL LETTER C, SOLIDUS, LATIN SMALL LETTER O#
			{8454, "c/u"},  // MA#* ( ? �� c/u ) CADA UNA �� LATIN SMALL LETTER C, SOLIDUS, LATIN SMALL LETTER U#
			{8458, "g"},    // MA# ( ? �� g ) SCRIPT SMALL G �� LATIN SMALL LETTER G#
			{8459, "H"},    // MA# ( ? �� H ) SCRIPT CAPITAL H �� LATIN CAPITAL LETTER H#
			{8460, "H"},    // MA# ( ? �� H ) BLACK-LETTER CAPITAL H �� LATIN CAPITAL LETTER H#
			{8461, "H"},    // MA# ( ? �� H ) DOUBLE-STRUCK CAPITAL H �� LATIN CAPITAL LETTER H#
			{8462, "h"},    // MA# ( ? �� h ) PLANCK CONSTANT �� LATIN SMALL LETTER H#
			{8464, "l"},    // MA# ( ? �� l ) SCRIPT CAPITAL I �� LATIN SMALL LETTER L# ��I��
			{8465, "l"},    // MA# ( ? �� l ) BLACK-LETTER CAPITAL I �� LATIN SMALL LETTER L# ��I��
			{8466, "L"},    // MA# ( ? �� L ) SCRIPT CAPITAL L �� LATIN CAPITAL LETTER L#
			{8467, "l"},    // MA# ( ? �� l ) SCRIPT SMALL L �� LATIN SMALL LETTER L#
			{8469, "N"},    // MA# ( ? �� N ) DOUBLE-STRUCK CAPITAL N �� LATIN CAPITAL LETTER N#
			{8470, "No"},   // MA#* ( �� �� No ) NUMERO SIGN �� LATIN CAPITAL LETTER N, LATIN SMALL LETTER O#
			{8473, "P"},    // MA# ( ? �� P ) DOUBLE-STRUCK CAPITAL P �� LATIN CAPITAL LETTER P#
			{8474, "Q"},    // MA# ( ? �� Q ) DOUBLE-STRUCK CAPITAL Q �� LATIN CAPITAL LETTER Q#
			{8475, "R"},    // MA# ( ? �� R ) SCRIPT CAPITAL R �� LATIN CAPITAL LETTER R#
			{8476, "R"},    // MA# ( ? �� R ) BLACK-LETTER CAPITAL R �� LATIN CAPITAL LETTER R#
			{8477, "R"},    // MA# ( ? �� R ) DOUBLE-STRUCK CAPITAL R �� LATIN CAPITAL LETTER R#
			{8481, "TEL"},  // MA#* ( �Y �� TEL ) TELEPHONE SIGN �� LATIN CAPITAL LETTER T, LATIN CAPITAL LETTER E, LATIN CAPITAL LETTER L#
			{8484, "Z"},    // MA# ( ? �� Z ) DOUBLE-STRUCK CAPITAL Z �� LATIN CAPITAL LETTER Z#
			{8488, "Z"},    // MA# ( ? �� Z ) BLACK-LETTER CAPITAL Z �� LATIN CAPITAL LETTER Z#
			{8490, "K"},    // MA# ( ? �� K ) KELVIN SIGN �� LATIN CAPITAL LETTER K#
			{8492, "B"},    // MA# ( ? �� B ) SCRIPT CAPITAL B �� LATIN CAPITAL LETTER B#
			{8493, "C"},    // MA# ( ? �� C ) BLACK-LETTER CAPITAL C �� LATIN CAPITAL LETTER C#
			{8494, "e"},    // MA# ( ? �� e ) ESTIMATED SYMBOL �� LATIN SMALL LETTER E#
			{8495, "e"},    // MA# ( ? �� e ) SCRIPT SMALL E �� LATIN SMALL LETTER E#
			{8496, "E"},    // MA# ( ? �� E ) SCRIPT CAPITAL E �� LATIN CAPITAL LETTER E#
			{8497, "F"},    // MA# ( ? �� F ) SCRIPT CAPITAL F �� LATIN CAPITAL LETTER F#
			{8499, "M"},    // MA# ( ? �� M ) SCRIPT CAPITAL M �� LATIN CAPITAL LETTER M#
			{8500, "o"},    // MA# ( ? �� o ) SCRIPT SMALL O �� LATIN SMALL LETTER O#
			{8505, "i"},    // MA# ( ? �� i ) INFORMATION SOURCE �� LATIN SMALL LETTER I#
			{8507, "FAX"},  // MA#* ( ? �� FAX ) FACSIMILE SIGN �� LATIN CAPITAL LETTER F, LATIN CAPITAL LETTER A, LATIN CAPITAL LETTER X#
			{8509, "y"},    // MA# ( ? �� y ) DOUBLE-STRUCK SMALL GAMMA �� LATIN SMALL LETTER Y# ���á�
			{8517, "D"},    // MA# ( ? �� D ) DOUBLE-STRUCK ITALIC CAPITAL D �� LATIN CAPITAL LETTER D#
			{8518, "d"},    // MA# ( ? �� d ) DOUBLE-STRUCK ITALIC SMALL D �� LATIN SMALL LETTER D#
			{8519, "e"},    // MA# ( ? �� e ) DOUBLE-STRUCK ITALIC SMALL E �� LATIN SMALL LETTER E#
			{8520, "i"},    // MA# ( ? �� i ) DOUBLE-STRUCK ITALIC SMALL I �� LATIN SMALL LETTER I#
			{8521, "j"},    // MA# ( ? �� j ) DOUBLE-STRUCK ITALIC SMALL J �� LATIN SMALL LETTER J#
			{8544, "l"},    // MA# ( �� �� l ) ROMAN NUMERAL ONE �� LATIN SMALL LETTER L# ��?��
			{8545, "ll"},   // MA# ( �� �� ll ) ROMAN NUMERAL TWO �� LATIN SMALL LETTER L, LATIN SMALL LETTER L# ��II��
			{8546, "lll"},  // MA# ( �� �� lll ) ROMAN NUMERAL THREE �� LATIN SMALL LETTER L, LATIN SMALL LETTER L, LATIN SMALL LETTER L# ��III��
			{8547, "lV"},   // MA# ( �� �� lV ) ROMAN NUMERAL FOUR �� LATIN SMALL LETTER L, LATIN CAPITAL LETTER V# ��IV��
			{8548, "V"},    // MA# ( �� �� V ) ROMAN NUMERAL FIVE �� LATIN CAPITAL LETTER V#
			{8549, "Vl"},   // MA# ( �� �� Vl ) ROMAN NUMERAL SIX �� LATIN CAPITAL LETTER V, LATIN SMALL LETTER L# ��VI��
			{8550, "Vll"},  // MA# ( �� �� Vll ) ROMAN NUMERAL SEVEN �� LATIN CAPITAL LETTER V, LATIN SMALL LETTER L, LATIN SMALL LETTER L# ��VII��
			{8551, "Vlll"}, // MA# ( �� �� Vlll ) ROMAN NUMERAL EIGHT �� LATIN CAPITAL LETTER V, LATIN SMALL LETTER L, LATIN SMALL LETTER L, LATIN SMALL LETTER L# ��VIII��
			{8552, "lX"},   // MA# ( �� �� lX ) ROMAN NUMERAL NINE �� LATIN SMALL LETTER L, LATIN CAPITAL LETTER X# ��IX��
			{8553, "X"},    // MA# ( �� �� X ) ROMAN NUMERAL TEN �� LATIN CAPITAL LETTER X#
			{8554, "Xl"},   // MA# ( �� �� Xl ) ROMAN NUMERAL ELEVEN �� LATIN CAPITAL LETTER X, LATIN SMALL LETTER L# ��XI��
			{8555, "Xll"},  // MA# ( �� �� Xll ) ROMAN NUMERAL TWELVE �� LATIN CAPITAL LETTER X, LATIN SMALL LETTER L, LATIN SMALL LETTER L# ��XII��
			{8556, "L"},    // MA# ( ? �� L ) ROMAN NUMERAL FIFTY �� LATIN CAPITAL LETTER L#
			{8557, "C"},    // MA# ( ? �� C ) ROMAN NUMERAL ONE HUNDRED �� LATIN CAPITAL LETTER C#
			{8558, "D"},    // MA# ( ? �� D ) ROMAN NUMERAL FIVE HUNDRED �� LATIN CAPITAL LETTER D#
			{8559, "M"},    // MA# ( ? �� M ) ROMAN NUMERAL ONE THOUSAND �� LATIN CAPITAL LETTER M#
			{8560, "i"},    // MA# ( �� �� i ) SMALL ROMAN NUMERAL ONE �� LATIN SMALL LETTER I#
			{8561, "ii"},   // MA# ( �� �� ii ) SMALL ROMAN NUMERAL TWO �� LATIN SMALL LETTER I, LATIN SMALL LETTER I#
			{8562, "iii"},  // MA# ( �� �� iii ) SMALL ROMAN NUMERAL THREE �� LATIN SMALL LETTER I, LATIN SMALL LETTER I, LATIN SMALL LETTER I#
			{8563, "iv"},   // MA# ( �� �� iv ) SMALL ROMAN NUMERAL FOUR �� LATIN SMALL LETTER I, LATIN SMALL LETTER V#
			{8564, "v"},    // MA# ( �� �� v ) SMALL ROMAN NUMERAL FIVE �� LATIN SMALL LETTER V#
			{8565, "vi"},   // MA# ( �� �� vi ) SMALL ROMAN NUMERAL SIX �� LATIN SMALL LETTER V, LATIN SMALL LETTER I#
			{8566, "vii"},  // MA# ( �� �� vii ) SMALL ROMAN NUMERAL SEVEN �� LATIN SMALL LETTER V, LATIN SMALL LETTER I, LATIN SMALL LETTER I#
			{8567, "viii"}, // MA# ( �� �� viii ) SMALL ROMAN NUMERAL EIGHT �� LATIN SMALL LETTER V, LATIN SMALL LETTER I, LATIN SMALL LETTER I, LATIN SMALL LETTER I#
			{8568, "ix"},   // MA# ( �� �� ix ) SMALL ROMAN NUMERAL NINE �� LATIN SMALL LETTER I, LATIN SMALL LETTER X#
			{8569, "x"},    // MA# ( �� �� x ) SMALL ROMAN NUMERAL TEN �� LATIN SMALL LETTER X#
			{8570, "xi"},   // MA# ( ? �� xi ) SMALL ROMAN NUMERAL ELEVEN �� LATIN SMALL LETTER X, LATIN SMALL LETTER I#
			{8571, "xii"},  // MA# ( ? �� xii ) SMALL ROMAN NUMERAL TWELVE �� LATIN SMALL LETTER X, LATIN SMALL LETTER I, LATIN SMALL LETTER I#
			{8572, "l"},    // MA# ( ? �� l ) SMALL ROMAN NUMERAL FIFTY �� LATIN SMALL LETTER L#
			{8573, "c"},    // MA# ( ? �� c ) SMALL ROMAN NUMERAL ONE HUNDRED �� LATIN SMALL LETTER C#
			{8574, "d"},    // MA# ( ? �� d ) SMALL ROMAN NUMERAL FIVE HUNDRED �� LATIN SMALL LETTER D#
			{8575, "rn"},   // MA# ( ? �� rn ) SMALL ROMAN NUMERAL ONE THOUSAND �� LATIN SMALL LETTER R, LATIN SMALL LETTER N# ��m��
			{8722, "-"},    // MA#* ( ? �� - ) MINUS SIGN �� HYPHEN-MINUS#
			{8725, "/"},    // MA#* ( �M �� / ) DIVISION SLASH �� SOLIDUS#
			{8726, "\\"},   // MA#* ( ? �� \ ) SET MINUS �� REVERSE SOLIDUS#
			{8727, "*"},    // MA#* ( ? �� * ) ASTERISK OPERATOR �� ASTERISK#
			{8734, "oo"},   // MA#* ( �� �� oo ) INFINITY �� LATIN SMALL LETTER O, LATIN SMALL LETTER O# ��?��
			{8739, "l"},    // MA#* ( �O �� l ) DIVIDES �� LATIN SMALL LETTER L# ��?��
			{8741, "ll"},   // MA#* ( �� �� ll ) PARALLEL TO �� LATIN SMALL LETTER L, LATIN SMALL LETTER L# ��||��
			{8744, "v"},    // MA#* ( �� �� v ) LOGICAL OR �� LATIN SMALL LETTER V#
			{8746, "U"},    // MA#* ( �� �� U ) UNION �� LATIN CAPITAL LETTER U# ��?��
			{8758, ":"},    // MA#* ( �� �� : ) RATIO �� COLON#
			{8764, "~"},    // MA#* ( ? �� ~ ) TILDE OPERATOR �� TILDE#
			{8810, "<<"},   // MA#* ( ? �� << ) MUCH LESS-THAN �� LESS-THAN SIGN, LESS-THAN SIGN#
			{8811, ">>"},   // MA#* ( ? �� >> ) MUCH GREATER-THAN �� GREATER-THAN SIGN, GREATER-THAN SIGN#
			{8868, "T"},    // MA#* ( ? �� T ) DOWN TACK �� LATIN CAPITAL LETTER T#
			{8897, "v"},    // MA#* ( ? �� v ) N-ARY LOGICAL OR �� LATIN SMALL LETTER V# ���š�
			{8899, "U"},    // MA#* ( ? �� U ) N-ARY UNION �� LATIN CAPITAL LETTER U# ���ȡ���?��
			{8920, "<<<"},  // MA#* ( ? �� <<< ) VERY MUCH LESS-THAN �� LESS-THAN SIGN, LESS-THAN SIGN, LESS-THAN SIGN#
			{8921, ">>>"},  // MA#* ( ? �� >>> ) VERY MUCH GREATER-THAN �� GREATER-THAN SIGN, GREATER-THAN SIGN, GREATER-THAN SIGN#
			{8959, "E"},    // MA#* ( ? �� E ) Z NOTATION BAG MEMBERSHIP �� LATIN CAPITAL LETTER E#
			{9075, "i"},    // MA#* ( ? �� i ) APL FUNCTIONAL SYMBOL IOTA �� LATIN SMALL LETTER I# ���ɡ�
			{9076, "p"},    // MA#* ( ? �� p ) APL FUNCTIONAL SYMBOL RHO �� LATIN SMALL LETTER P# ���ѡ�
			{9082, "a"},    // MA#* ( ? �� a ) APL FUNCTIONAL SYMBOL ALPHA �� LATIN SMALL LETTER A# ������
			{9213, "l"},    // MA#* ( ? �� l ) POWER ON SYMBOL �� LATIN SMALL LETTER L# ��I��
			{9290, "\\\\"}, // MA#* ( ? �� \\ ) OCR DOUBLE BACKSLASH �� REVERSE SOLIDUS, REVERSE SOLIDUS#
			{9332, "(l)"},  // MA#* ( �� �� (l) ) PARENTHESIZED DIGIT ONE �� LEFT PARENTHESIS, LATIN SMALL LETTER L, RIGHT PARENTHESIS# ��(1)��
			{9333, "(2)"},  // MA#* ( �� �� (2) ) PARENTHESIZED DIGIT TWO �� LEFT PARENTHESIS, DIGIT TWO, RIGHT PARENTHESIS#
			{9334, "(3)"},  // MA#* ( �� �� (3) ) PARENTHESIZED DIGIT THREE �� LEFT PARENTHESIS, DIGIT THREE, RIGHT PARENTHESIS#
			{9335, "(4)"},  // MA#* ( �� �� (4) ) PARENTHESIZED DIGIT FOUR �� LEFT PARENTHESIS, DIGIT FOUR, RIGHT PARENTHESIS#
			{9336, "(5)"},  // MA#* ( �� �� (5) ) PARENTHESIZED DIGIT FIVE �� LEFT PARENTHESIS, DIGIT FIVE, RIGHT PARENTHESIS#
			{9337, "(6)"},  // MA#* ( �� �� (6) ) PARENTHESIZED DIGIT SIX �� LEFT PARENTHESIS, DIGIT SIX, RIGHT PARENTHESIS#
			{9338, "(7)"},  // MA#* ( �� �� (7) ) PARENTHESIZED DIGIT SEVEN �� LEFT PARENTHESIS, DIGIT SEVEN, RIGHT PARENTHESIS#
			{9339, "(8)"},  // MA#* ( �� �� (8) ) PARENTHESIZED DIGIT EIGHT �� LEFT PARENTHESIS, DIGIT EIGHT, RIGHT PARENTHESIS#
			{9340, "(9)"},  // MA#* ( �� �� (9) ) PARENTHESIZED DIGIT NINE �� LEFT PARENTHESIS, DIGIT NINE, RIGHT PARENTHESIS#
			{9341, "(lO)"}, // MA#* ( �� �� (lO) ) PARENTHESIZED NUMBER TEN �� LEFT PARENTHESIS, LATIN SMALL LETTER L, LATIN CAPITAL LETTER O, RIGHT PARENTHESIS# ��(10)��
			{9342, "(ll)"}, // MA#* ( �� �� (ll) ) PARENTHESIZED NUMBER ELEVEN �� LEFT PARENTHESIS, LATIN SMALL LETTER L, LATIN SMALL LETTER L, RIGHT PARENTHESIS# ��(11)��
			{9343, "(l2)"}, // MA#* ( �� �� (l2) ) PARENTHESIZED NUMBER TWELVE �� LEFT PARENTHESIS, LATIN SMALL LETTER L, DIGIT TWO, RIGHT PARENTHESIS# ��(12)��
			{9344, "(l3)"}, // MA#* ( �� �� (l3) ) PARENTHESIZED NUMBER THIRTEEN �� LEFT PARENTHESIS, LATIN SMALL LETTER L, DIGIT THREE, RIGHT PARENTHESIS# ��(13)��
			{9345, "(l4)"}, // MA#* ( �� �� (l4) ) PARENTHESIZED NUMBER FOURTEEN �� LEFT PARENTHESIS, LATIN SMALL LETTER L, DIGIT FOUR, RIGHT PARENTHESIS# ��(14)��
			{9346, "(l5)"}, // MA#* ( �� �� (l5) ) PARENTHESIZED NUMBER FIFTEEN �� LEFT PARENTHESIS, LATIN SMALL LETTER L, DIGIT FIVE, RIGHT PARENTHESIS# ��(15)��
			{9347, "(l6)"}, // MA#* ( �� �� (l6) ) PARENTHESIZED NUMBER SIXTEEN �� LEFT PARENTHESIS, LATIN SMALL LETTER L, DIGIT SIX, RIGHT PARENTHESIS# ��(16)��
			{9348, "(l7)"}, // MA#* ( �� �� (l7) ) PARENTHESIZED NUMBER SEVENTEEN �� LEFT PARENTHESIS, LATIN SMALL LETTER L, DIGIT SEVEN, RIGHT PARENTHESIS# ��(17)��
			{9349, "(l8)"}, // MA#* ( �� �� (l8) ) PARENTHESIZED NUMBER EIGHTEEN �� LEFT PARENTHESIS, LATIN SMALL LETTER L, DIGIT EIGHT, RIGHT PARENTHESIS# ��(18)��
			{9350, "(l9)"}, // MA#* ( �� �� (l9) ) PARENTHESIZED NUMBER NINETEEN �� LEFT PARENTHESIS, LATIN SMALL LETTER L, DIGIT NINE, RIGHT PARENTHESIS# ��(19)��
			{9351, "(2O)"}, // MA#* ( �� �� (2O) ) PARENTHESIZED NUMBER TWENTY �� LEFT PARENTHESIS, DIGIT TWO, LATIN CAPITAL LETTER O, RIGHT PARENTHESIS# ��(20)��
			{9352, "l."},   // MA#* ( �� �� l. ) DIGIT ONE FULL STOP �� LATIN SMALL LETTER L, FULL STOP# ��1.��
			{9353, "2."},   // MA#* ( �� �� 2. ) DIGIT TWO FULL STOP �� DIGIT TWO, FULL STOP#
			{9354, "3."},   // MA#* ( �� �� 3. ) DIGIT THREE FULL STOP �� DIGIT THREE, FULL STOP#
			{9355, "4."},   // MA#* ( �� �� 4. ) DIGIT FOUR FULL STOP �� DIGIT FOUR, FULL STOP#
			{9356, "5."},   // MA#* ( �� �� 5. ) DIGIT FIVE FULL STOP �� DIGIT FIVE, FULL STOP#
			{9357, "6."},   // MA#* ( �� �� 6. ) DIGIT SIX FULL STOP �� DIGIT SIX, FULL STOP#
			{9358, "7."},   // MA#* ( �� �� 7. ) DIGIT SEVEN FULL STOP �� DIGIT SEVEN, FULL STOP#
			{9359, "8."},   // MA#* ( �� �� 8. ) DIGIT EIGHT FULL STOP �� DIGIT EIGHT, FULL STOP#
			{9360, "9."},   // MA#* ( �� �� 9. ) DIGIT NINE FULL STOP �� DIGIT NINE, FULL STOP#
			{9361, "lO."},  // MA#* ( �� �� lO. ) NUMBER TEN FULL STOP �� LATIN SMALL LETTER L, LATIN CAPITAL LETTER O, FULL STOP# ��10.��
			{9362, "ll."},  // MA#* ( �� �� ll. ) NUMBER ELEVEN FULL STOP �� LATIN SMALL LETTER L, LATIN SMALL LETTER L, FULL STOP# ��11.��
			{9363, "l2."},  // MA#* ( �� �� l2. ) NUMBER TWELVE FULL STOP �� LATIN SMALL LETTER L, DIGIT TWO, FULL STOP# ��12.��
			{9364, "l3."},  // MA#* ( �� �� l3. ) NUMBER THIRTEEN FULL STOP �� LATIN SMALL LETTER L, DIGIT THREE, FULL STOP# ��13.��
			{9365, "l4."},  // MA#* ( �� �� l4. ) NUMBER FOURTEEN FULL STOP �� LATIN SMALL LETTER L, DIGIT FOUR, FULL STOP# ��14.��
			{9366, "l5."},  // MA#* ( �� �� l5. ) NUMBER FIFTEEN FULL STOP �� LATIN SMALL LETTER L, DIGIT FIVE, FULL STOP# ��15.��
			{9367, "l6."},  // MA#* ( �� �� l6. ) NUMBER SIXTEEN FULL STOP �� LATIN SMALL LETTER L, DIGIT SIX, FULL STOP# ��16.��
			{9368, "l7."},  // MA#* ( �� �� l7. ) NUMBER SEVENTEEN FULL STOP �� LATIN SMALL LETTER L, DIGIT SEVEN, FULL STOP# ��17.��
			{9369, "l8."},  // MA#* ( �� �� l8. ) NUMBER EIGHTEEN FULL STOP �� LATIN SMALL LETTER L, DIGIT EIGHT, FULL STOP# ��18.��
			{9370, "l9."},  // MA#* ( �� �� l9. ) NUMBER NINETEEN FULL STOP �� LATIN SMALL LETTER L, DIGIT NINE, FULL STOP# ��19.��
			{9371, "2O."},  // MA#* ( �� �� 2O. ) NUMBER TWENTY FULL STOP �� DIGIT TWO, LATIN CAPITAL LETTER O, FULL STOP# ��20.��
			{9372, "(a)"},  // MA#* ( ? �� (a) ) PARENTHESIZED LATIN SMALL LETTER A �� LEFT PARENTHESIS, LATIN SMALL LETTER A, RIGHT PARENTHESIS#
			{9373, "(b)"},  // MA#* ( ? �� (b) ) PARENTHESIZED LATIN SMALL LETTER B �� LEFT PARENTHESIS, LATIN SMALL LETTER B, RIGHT PARENTHESIS#
			{9374, "(c)"},  // MA#* ( ? �� (c) ) PARENTHESIZED LATIN SMALL LETTER C �� LEFT PARENTHESIS, LATIN SMALL LETTER C, RIGHT PARENTHESIS#
			{9375, "(d)"},  // MA#* ( ? �� (d) ) PARENTHESIZED LATIN SMALL LETTER D �� LEFT PARENTHESIS, LATIN SMALL LETTER D, RIGHT PARENTHESIS#
			{9376, "(e)"},  // MA#* ( ? �� (e) ) PARENTHESIZED LATIN SMALL LETTER E �� LEFT PARENTHESIS, LATIN SMALL LETTER E, RIGHT PARENTHESIS#
			{9377, "(f)"},  // MA#* ( ? �� (f) ) PARENTHESIZED LATIN SMALL LETTER F �� LEFT PARENTHESIS, LATIN SMALL LETTER F, RIGHT PARENTHESIS#
			{9378, "(g)"},  // MA#* ( ? �� (g) ) PARENTHESIZED LATIN SMALL LETTER G �� LEFT PARENTHESIS, LATIN SMALL LETTER G, RIGHT PARENTHESIS#
			{9379, "(h)"},  // MA#* ( ? �� (h) ) PARENTHESIZED LATIN SMALL LETTER H �� LEFT PARENTHESIS, LATIN SMALL LETTER H, RIGHT PARENTHESIS#
			{9380, "(i)"},  // MA#* ( ? �� (i) ) PARENTHESIZED LATIN SMALL LETTER I �� LEFT PARENTHESIS, LATIN SMALL LETTER I, RIGHT PARENTHESIS#
			{9381, "(j)"},  // MA#* ( ? �� (j) ) PARENTHESIZED LATIN SMALL LETTER J �� LEFT PARENTHESIS, LATIN SMALL LETTER J, RIGHT PARENTHESIS#
			{9382, "(k)"},  // MA#* ( ? �� (k) ) PARENTHESIZED LATIN SMALL LETTER K �� LEFT PARENTHESIS, LATIN SMALL LETTER K, RIGHT PARENTHESIS#
			{9383, "(l)"},  // MA#* ( ? �� (l) ) PARENTHESIZED LATIN SMALL LETTER L �� LEFT PARENTHESIS, LATIN SMALL LETTER L, RIGHT PARENTHESIS#
			{9384, "(rn)"}, // MA#* ( ? �� (rn) ) PARENTHESIZED LATIN SMALL LETTER M �� LEFT PARENTHESIS, LATIN SMALL LETTER R, LATIN SMALL LETTER N, RIGHT PARENTHESIS# ��(m)��
			{9385, "(n)"},  // MA#* ( ? �� (n) ) PARENTHESIZED LATIN SMALL LETTER N �� LEFT PARENTHESIS, LATIN SMALL LETTER N, RIGHT PARENTHESIS#
			{9386, "(o)"},  // MA#* ( ? �� (o) ) PARENTHESIZED LATIN SMALL LETTER O �� LEFT PARENTHESIS, LATIN SMALL LETTER O, RIGHT PARENTHESIS#
			{9387, "(p)"},  // MA#* ( ? �� (p) ) PARENTHESIZED LATIN SMALL LETTER P �� LEFT PARENTHESIS, LATIN SMALL LETTER P, RIGHT PARENTHESIS#
			{9388, "(q)"},  // MA#* ( ? �� (q) ) PARENTHESIZED LATIN SMALL LETTER Q �� LEFT PARENTHESIS, LATIN SMALL LETTER Q, RIGHT PARENTHESIS#
			{9389, "(r)"},  // MA#* ( ? �� (r) ) PARENTHESIZED LATIN SMALL LETTER R �� LEFT PARENTHESIS, LATIN SMALL LETTER R, RIGHT PARENTHESIS#
			{9390, "(s)"},  // MA#* ( ? �� (s) ) PARENTHESIZED LATIN SMALL LETTER S �� LEFT PARENTHESIS, LATIN SMALL LETTER S, RIGHT PARENTHESIS#
			{9391, "(t)"},  // MA#* ( ? �� (t) ) PARENTHESIZED LATIN SMALL LETTER T �� LEFT PARENTHESIS, LATIN SMALL LETTER T, RIGHT PARENTHESIS#
			{9392, "(u)"},  // MA#* ( ? �� (u) ) PARENTHESIZED LATIN SMALL LETTER U �� LEFT PARENTHESIS, LATIN SMALL LETTER U, RIGHT PARENTHESIS#
			{9393, "(v)"},  // MA#* ( ? �� (v) ) PARENTHESIZED LATIN SMALL LETTER V �� LEFT PARENTHESIS, LATIN SMALL LETTER V, RIGHT PARENTHESIS#
			{9394, "(w)"},  // MA#* ( ? �� (w) ) PARENTHESIZED LATIN SMALL LETTER W �� LEFT PARENTHESIS, LATIN SMALL LETTER W, RIGHT PARENTHESIS#
			{9395, "(x)"},  // MA#* ( ? �� (x) ) PARENTHESIZED LATIN SMALL LETTER X �� LEFT PARENTHESIS, LATIN SMALL LETTER X, RIGHT PARENTHESIS#
			{9396, "(y)"},  // MA#* ( ? �� (y) ) PARENTHESIZED LATIN SMALL LETTER Y �� LEFT PARENTHESIS, LATIN SMALL LETTER Y, RIGHT PARENTHESIS#
			{9397, "(z)"},  // MA#* ( ? �� (z) ) PARENTHESIZED LATIN SMALL LETTER Z �� LEFT PARENTHESIS, LATIN SMALL LETTER Z, RIGHT PARENTHESIS#
			{9585, "/"},    // MA#* ( �u �� / ) BOX DRAWINGS LIGHT DIAGONAL UPPER RIGHT TO LOWER LEFT �� SOLIDUS#
			{9587, "X"},    // MA#* ( �w �� X ) BOX DRAWINGS LIGHT DIAGONAL CROSS �� LATIN CAPITAL LETTER X#
			{10088, "("},   // MA#* ( ? �� ( ) MEDIUM LEFT PARENTHESIS ORNAMENT �� LEFT PARENTHESIS#
			{10089, ")"},   // MA#* ( ? �� ) ) MEDIUM RIGHT PARENTHESIS ORNAMENT �� RIGHT PARENTHESIS#
			{10094, "<"},   // MA#* ( ? �� < ) HEAVY LEFT-POINTING ANGLE QUOTATION MARK ORNAMENT �� LESS-THAN SIGN# ��?��
			{10095, ">"},   // MA#* ( ? �� > ) HEAVY RIGHT-POINTING ANGLE QUOTATION MARK ORNAMENT �� GREATER-THAN SIGN# ��?��
			{10098, "("},   // MA#* ( ? �� ( ) LIGHT LEFT TORTOISE SHELL BRACKET ORNAMENT �� LEFT PARENTHESIS# ������
			{10099, ")"},   // MA#* ( ? �� ) ) LIGHT RIGHT TORTOISE SHELL BRACKET ORNAMENT �� RIGHT PARENTHESIS# ������
			{10100, "{"},   // MA#* ( ? �� { ) MEDIUM LEFT CURLY BRACKET ORNAMENT �� LEFT CURLY BRACKET#
			{10101, "}"},   // MA#* ( ? �� } ) MEDIUM RIGHT CURLY BRACKET ORNAMENT �� RIGHT CURLY BRACKET#
			{10133, "+"},   // MA#* ( ? �� + ) HEAVY PLUS SIGN �� PLUS SIGN#
			{10134, "-"},   // MA#* ( ? �� - ) HEAVY MINUS SIGN �� HYPHEN-MINUS# ��?��
			{10187, "/"},   // MA#* ( ? �� / ) MATHEMATICAL RISING DIAGONAL �� SOLIDUS#
			{10189, "\\"},  // MA#* ( ? �� \ ) MATHEMATICAL FALLING DIAGONAL �� REVERSE SOLIDUS#
			{10201, "T"},   // MA#* ( ? �� T ) LARGE DOWN TACK �� LATIN CAPITAL LETTER T#
			{10539, "x"},   // MA#* ( ? �� x ) RISING DIAGONAL CROSSING FALLING DIAGONAL �� LATIN SMALL LETTER X#
			{10540, "x"},   // MA#* ( ? �� x ) FALLING DIAGONAL CROSSING RISING DIAGONAL �� LATIN SMALL LETTER X#
			{10741, "\\"},  // MA#* ( ? �� \ ) REVERSE SOLIDUS OPERATOR �� REVERSE SOLIDUS#
			{10744, "/"},   // MA#* ( ? �� / ) BIG SOLIDUS �� SOLIDUS#
			{10745, "\\"},  // MA#* ( ? �� \ ) BIG REVERSE SOLIDUS �� REVERSE SOLIDUS#
			{10784, ">>"},  // MA#* ( ? �� >> ) Z NOTATION SCHEMA PIPING �� GREATER-THAN SIGN, GREATER-THAN SIGN# ��?��
			{10799, "x"},   // MA#* ( ? �� x ) VECTOR OR CROSS PRODUCT �� LATIN SMALL LETTER X# ������
			{10868, "::="}, // MA#* ( ? �� ::= ) DOUBLE COLON EQUAL �� COLON, COLON, EQUALS SIGN#
			{10869, "=="},  // MA#* ( ? �� == ) TWO CONSECUTIVE EQUALS SIGNS �� EQUALS SIGN, EQUALS SIGN#
			{10870, "==="}, // MA#* ( ? �� === ) THREE CONSECUTIVE EQUALS SIGNS �� EQUALS SIGN, EQUALS SIGN, EQUALS SIGN#
			{10917, "><"},  // MA#* ( ? �� >< ) GREATER-THAN BESIDE LESS-THAN �� GREATER-THAN SIGN, LESS-THAN SIGN#
			{11003, "///"}, // MA#* ( ? �� /// ) TRIPLE SOLIDUS BINARY RELATION �� SOLIDUS, SOLIDUS, SOLIDUS#
			{11005, "//"},  // MA#* ( ? �� // ) DOUBLE SOLIDUS OPERATOR �� SOLIDUS, SOLIDUS#
			{11397, "r"},   // MA# ( ? �� r ) COPTIC SMALL LETTER GAMMA �� LATIN SMALL LETTER R# ���ԡ�
			{11406, "H"},   // MA# ( ? �� H ) COPTIC CAPITAL LETTER HATE �� LATIN CAPITAL LETTER H# ������
			{11410, "l"},   // MA# ( ? �� l ) COPTIC CAPITAL LETTER IAUDA �� LATIN SMALL LETTER L# ��?��
			{11412, "K"},   // MA# ( ? �� K ) COPTIC CAPITAL LETTER KAPA �� LATIN CAPITAL LETTER K# ������
			{11416, "M"},   // MA# ( ? �� M ) COPTIC CAPITAL LETTER MI �� LATIN CAPITAL LETTER M#
			{11418, "N"},   // MA# ( ? �� N ) COPTIC CAPITAL LETTER NI �� LATIN CAPITAL LETTER N#
			{11422, "O"},   // MA# ( ? �� O ) COPTIC CAPITAL LETTER O �� LATIN CAPITAL LETTER O#
			{11423, "o"},   // MA# ( ? �� o ) COPTIC SMALL LETTER O �� LATIN SMALL LETTER O#
			{11426, "P"},   // MA# ( ? �� P ) COPTIC CAPITAL LETTER RO �� LATIN CAPITAL LETTER P#
			{11427, "p"},   // MA# ( ? �� p ) COPTIC SMALL LETTER RO �� LATIN SMALL LETTER P# ���ѡ�
			{11428, "C"},   // MA# ( ? �� C ) COPTIC CAPITAL LETTER SIMA �� LATIN CAPITAL LETTER C# ��?��
			{11429, "c"},   // MA# ( ? �� c ) COPTIC SMALL LETTER SIMA �� LATIN SMALL LETTER C# ��?��
			{11430, "T"},   // MA# ( ? �� T ) COPTIC CAPITAL LETTER TAU �� LATIN CAPITAL LETTER T#
			{11432, "Y"},   // MA# ( ? �� Y ) COPTIC CAPITAL LETTER UA �� LATIN CAPITAL LETTER Y#
			{11436, "X"},   // MA# ( ? �� X ) COPTIC CAPITAL LETTER KHI �� LATIN CAPITAL LETTER X# ������
			{11450, "-"},   // MA# ( ? �� - ) COPTIC CAPITAL LETTER DIALECT-P NI �� HYPHEN-MINUS# ��?��
			{11462, "/"},   // MA# ( ? �� / ) COPTIC CAPITAL LETTER OLD COPTIC ESH �� SOLIDUS#
			{11466, "9"},   // MA# ( ? �� 9 ) COPTIC CAPITAL LETTER DIALECT-P HORI �� DIGIT NINE#
			{11468, "3"},   // MA# ( ? �� 3 ) COPTIC CAPITAL LETTER OLD COPTIC HORI �� DIGIT THREE# ��?����?��
			{11472, "L"},   // MA# ( ? �� L ) COPTIC CAPITAL LETTER L-SHAPED HA �� LATIN CAPITAL LETTER L#
			{11474, "6"},   // MA# ( ? �� 6 ) COPTIC CAPITAL LETTER OLD COPTIC HEI �� DIGIT SIX#
			{11513, "\\\\"},// MA#* ( ? �� \\ ) COPTIC OLD NUBIAN FULL STOP �� REVERSE SOLIDUS, REVERSE SOLIDUS#
			{11576, "V"},   // MA# ( ? �� V ) TIFINAGH LETTER YADH �� LATIN CAPITAL LETTER V#
			{11577, "E"},   // MA# ( ? �� E ) TIFINAGH LETTER YADD �� LATIN CAPITAL LETTER E#
			{11599, "l"},   // MA# ( ? �� l ) TIFINAGH LETTER YAN �� LATIN SMALL LETTER L# ��?��
			{11601, "!"},   // MA# ( ? �� ! ) TIFINAGH LETTER TUAREG YANG �� EXCLAMATION MARK#
			{11604, "O"},   // MA# ( ? �� O ) TIFINAGH LETTER YAR �� LATIN CAPITAL LETTER O#
			{11605, "Q"},   // MA# ( ? �� Q ) TIFINAGH LETTER YARR �� LATIN CAPITAL LETTER Q#
			{11613, "X"},   // MA# ( ? �� X ) TIFINAGH LETTER YATH �� LATIN CAPITAL LETTER X#
			{11816, "(("},  // MA#* ( ? �� (( ) LEFT DOUBLE PARENTHESIS �� LEFT PARENTHESIS, LEFT PARENTHESIS#
			{11817, "))"},  // MA#* ( ? �� )) ) RIGHT DOUBLE PARENTHESIS �� RIGHT PARENTHESIS, RIGHT PARENTHESIS#
			{11840, "="},   // MA#* ( ? �� = ) DOUBLE HYPHEN �� EQUALS SIGN#
			{12034, "\\"},  // MA#* ( ? �� \ ) KANGXI RADICAL DOT �� REVERSE SOLIDUS#
			{12035, "/"},   // MA#* ( ? �� / ) KANGXI RADICAL SLASH �� SOLIDUS#
			{12291, "\""},  // MA#* ( �� �� '' ) DITTO MARK �� APOSTROPHE, APOSTROPHE# �������"��# Converted to a quote.
			{12295, "O"},   // MA# ( �� �� O ) IDEOGRAPHIC NUMBER ZERO �� LATIN CAPITAL LETTER O#
			{12308, "("},   // MA#* ( �� �� ( ) LEFT TORTOISE SHELL BRACKET �� LEFT PARENTHESIS#
			{12309, ")"},   // MA#* ( �� �� ) ) RIGHT TORTOISE SHELL BRACKET �� RIGHT PARENTHESIS#
			{12339, "/"},   // MA# ( ? �� / ) VERTICAL KANA REPEAT MARK UPPER HALF �� SOLIDUS#
			{12448, "="},   // MA#* ( ? �� = ) KATAKANA-HIRAGANA DOUBLE HYPHEN �� EQUALS SIGN#
			{12494, "/"},   // MA# ( �� �� / ) KATAKANA LETTER NO �� SOLIDUS# ��?��
			{12755, "/"},   // MA#* ( ? �� / ) CJK STROKE SP �� SOLIDUS# ��?��
			{12756, "\\"},  // MA#* ( ? �� \ ) CJK STROKE D �� REVERSE SOLIDUS# ��?��
			{20022, "\\"},  // MA# ( ؼ �� \ ) CJK UNIFIED IDEOGRAPH-4E36 �� REVERSE SOLIDUS# ��?��
			{20031, "/"},   // MA# ( د �� / ) CJK UNIFIED IDEOGRAPH-4E3F �� SOLIDUS# ��?��
			{42192, "B"},   // MA# ( ? �� B ) LISU LETTER BA �� LATIN CAPITAL LETTER B#
			{42193, "P"},   // MA# ( ? �� P ) LISU LETTER PA �� LATIN CAPITAL LETTER P#
			{42194, "d"},   // MA# ( ? �� d ) LISU LETTER PHA �� LATIN SMALL LETTER D#
			{42195, "D"},   // MA# ( ? �� D ) LISU LETTER DA �� LATIN CAPITAL LETTER D#
			{42196, "T"},   // MA# ( ? �� T ) LISU LETTER TA �� LATIN CAPITAL LETTER T#
			{42198, "G"},   // MA# ( ? �� G ) LISU LETTER GA �� LATIN CAPITAL LETTER G#
			{42199, "K"},   // MA# ( ? �� K ) LISU LETTER KA �� LATIN CAPITAL LETTER K#
			{42201, "J"},   // MA# ( ? �� J ) LISU LETTER JA �� LATIN CAPITAL LETTER J#
			{42202, "C"},   // MA# ( ? �� C ) LISU LETTER CA �� LATIN CAPITAL LETTER C#
			{42204, "Z"},   // MA# ( ? �� Z ) LISU LETTER DZA �� LATIN CAPITAL LETTER Z#
			{42205, "F"},   // MA# ( ? �� F ) LISU LETTER TSA �� LATIN CAPITAL LETTER F#
			{42207, "M"},   // MA# ( ? �� M ) LISU LETTER MA �� LATIN CAPITAL LETTER M#
			{42208, "N"},   // MA# ( ? �� N ) LISU LETTER NA �� LATIN CAPITAL LETTER N#
			{42209, "L"},   // MA# ( ? �� L ) LISU LETTER LA �� LATIN CAPITAL LETTER L#
			{42210, "S"},   // MA# ( ? �� S ) LISU LETTER SA �� LATIN CAPITAL LETTER S#
			{42211, "R"},   // MA# ( ? �� R ) LISU LETTER ZHA �� LATIN CAPITAL LETTER R#
			{42214, "V"},   // MA# ( ? �� V ) LISU LETTER HA �� LATIN CAPITAL LETTER V#
			{42215, "H"},   // MA# ( ? �� H ) LISU LETTER XA �� LATIN CAPITAL LETTER H#
			{42218, "W"},   // MA# ( ? �� W ) LISU LETTER WA �� LATIN CAPITAL LETTER W#
			{42219, "X"},   // MA# ( ? �� X ) LISU LETTER SHA �� LATIN CAPITAL LETTER X#
			{42220, "Y"},   // MA# ( ? �� Y ) LISU LETTER YA �� LATIN CAPITAL LETTER Y#
			{42222, "A"},   // MA# ( ? �� A ) LISU LETTER A �� LATIN CAPITAL LETTER A#
			{42224, "E"},   // MA# ( ? �� E ) LISU LETTER E �� LATIN CAPITAL LETTER E#
			{42226, "l"},   // MA# ( ? �� l ) LISU LETTER I �� LATIN SMALL LETTER L# ��I��
			{42227, "O"},   // MA# ( ? �� O ) LISU LETTER O �� LATIN CAPITAL LETTER O#
			{42228, "U"},   // MA# ( ? �� U ) LISU LETTER U �� LATIN CAPITAL LETTER U#
			{42232, "."},   // MA# ( ? �� . ) LISU LETTER TONE MYA TI �� FULL STOP#
			{42233, ","},   // MA# ( ? �� , ) LISU LETTER TONE NA PO �� COMMA#
			{42234, ".."},  // MA# ( ? �� .. ) LISU LETTER TONE MYA CYA �� FULL STOP, FULL STOP#
			{42235, ".,"},  // MA# ( ? �� ., ) LISU LETTER TONE MYA BO �� FULL STOP, COMMA#
			{42237, ":"},   // MA# ( ? �� : ) LISU LETTER TONE MYA JEU �� COLON#
			{42238, "-."},  // MA#* ( ? �� -. ) LISU PUNCTUATION COMMA �� HYPHEN-MINUS, FULL STOP#
			{42239, "="},   // MA#* ( ? �� = ) LISU PUNCTUATION FULL STOP �� EQUALS SIGN#
			{42510, "."},   // MA#* ( ? �� . ) VAI FULL STOP �� FULL STOP#
			{42564, "2"},   // MA# ( ? �� 2 ) CYRILLIC CAPITAL LETTER REVERSED DZE �� DIGIT TWO# ��?��
			{42567, "i"},   // MA# ( ? �� i ) CYRILLIC SMALL LETTER IOTA �� LATIN SMALL LETTER I# ���ɡ�
			{42648, "OO"},  // MA# ( ? �� OO ) CYRILLIC CAPITAL LETTER DOUBLE O �� LATIN CAPITAL LETTER O, LATIN CAPITAL LETTER O#
			{42649, "oo"},  // MA# ( ? �� oo ) CYRILLIC SMALL LETTER DOUBLE O �� LATIN SMALL LETTER O, LATIN SMALL LETTER O#
			{42719, "V"},   // MA# ( ? �� V ) BAMUM LETTER KO �� LATIN CAPITAL LETTER V#
			{42731, "?"},   // MA# ( ? �� ? ) BAMUM LETTER NTUU �� QUESTION MARK# ��?��
			{42735, "2"},   // MA# ( ? �� 2 ) BAMUM LETTER KOGHOM �� DIGIT TWO# ��?��
			{42792, "T3"},  // MA# ( ? �� T3 ) LATIN CAPITAL LETTER TZ �� LATIN CAPITAL LETTER T, DIGIT THREE# ��T?��
			{42801, "s"},   // MA# ( ? �� s ) LATIN LETTER SMALL CAPITAL S �� LATIN SMALL LETTER S#
			{42802, "AA"},  // MA# ( ? �� AA ) LATIN CAPITAL LETTER AA �� LATIN CAPITAL LETTER A, LATIN CAPITAL LETTER A#
			{42803, "aa"},  // MA# ( ? �� aa ) LATIN SMALL LETTER AA �� LATIN SMALL LETTER A, LATIN SMALL LETTER A#
			{42804, "AO"},  // MA# ( ? �� AO ) LATIN CAPITAL LETTER AO �� LATIN CAPITAL LETTER A, LATIN CAPITAL LETTER O#
			{42805, "ao"},  // MA# ( ? �� ao ) LATIN SMALL LETTER AO �� LATIN SMALL LETTER A, LATIN SMALL LETTER O#
			{42806, "AU"},  // MA# ( ? �� AU ) LATIN CAPITAL LETTER AU �� LATIN CAPITAL LETTER A, LATIN CAPITAL LETTER U#
			{42807, "au"},  // MA# ( ? �� au ) LATIN SMALL LETTER AU �� LATIN SMALL LETTER A, LATIN SMALL LETTER U#
			{42808, "AV"},  // MA# ( ? �� AV ) LATIN CAPITAL LETTER AV �� LATIN CAPITAL LETTER A, LATIN CAPITAL LETTER V#
			{42809, "av"},  // MA# ( ? �� av ) LATIN SMALL LETTER AV �� LATIN SMALL LETTER A, LATIN SMALL LETTER V#
			{42810, "AV"},  // MA# ( ? �� AV ) LATIN CAPITAL LETTER AV WITH HORIZONTAL BAR �� LATIN CAPITAL LETTER A, LATIN CAPITAL LETTER V#
			{42811, "av"},  // MA# ( ? �� av ) LATIN SMALL LETTER AV WITH HORIZONTAL BAR �� LATIN SMALL LETTER A, LATIN SMALL LETTER V#
			{42812, "AY"},  // MA# ( ? �� AY ) LATIN CAPITAL LETTER AY �� LATIN CAPITAL LETTER A, LATIN CAPITAL LETTER Y#
			{42813, "ay"},  // MA# ( ? �� ay ) LATIN SMALL LETTER AY �� LATIN SMALL LETTER A, LATIN SMALL LETTER Y#
			{42830, "OO"},  // MA# ( ? �� OO ) LATIN CAPITAL LETTER OO �� LATIN CAPITAL LETTER O, LATIN CAPITAL LETTER O#
			{42831, "oo"},  // MA# ( ? �� oo ) LATIN SMALL LETTER OO �� LATIN SMALL LETTER O, LATIN SMALL LETTER O#
			{42842, "2"},   // MA# ( ? �� 2 ) LATIN CAPITAL LETTER R ROTUNDA �� DIGIT TWO#
			{42858, "3"},   // MA# ( ? �� 3 ) LATIN CAPITAL LETTER ET �� DIGIT THREE#
			{42862, "9"},   // MA# ( ? �� 9 ) LATIN CAPITAL LETTER CON �� DIGIT NINE#
			{42871, "tf"},  // MA# ( ? �� tf ) LATIN SMALL LETTER TUM �� LATIN SMALL LETTER T, LATIN SMALL LETTER F#
			{42872, "&"},   // MA# ( ? �� & ) LATIN SMALL LETTER UM �� AMPERSAND#
			{42889, ":"},   // MA#* ( ? �� : ) MODIFIER LETTER COLON �� COLON#
			{42892, "'"},   // MA# ( ? �� ' ) LATIN SMALL LETTER SALTILLO �� APOSTROPHE#
			{42904, "F"},   // MA# ( ? �� F ) LATIN CAPITAL LETTER F WITH STROKE �� LATIN CAPITAL LETTER F#
			{42905, "f"},   // MA# ( ? �� f ) LATIN SMALL LETTER F WITH STROKE �� LATIN SMALL LETTER F#
			{42911, "u"},   // MA# ( ? �� u ) LATIN SMALL LETTER VOLAPUK UE �� LATIN SMALL LETTER U#
			{42923, "3"},   // MA# ( ? �� 3 ) LATIN CAPITAL LETTER REVERSED OPEN E �� DIGIT THREE#
			{42930, "J"},   // MA# ( ? �� J ) LATIN CAPITAL LETTER J WITH CROSSED-TAIL �� LATIN CAPITAL LETTER J#
			{42931, "X"},   // MA# ( ? �� X ) LATIN CAPITAL LETTER CHI �� LATIN CAPITAL LETTER X#
			{42932, "B"},   // MA# ( ? �� B ) LATIN CAPITAL LETTER BETA �� LATIN CAPITAL LETTER B#
			{43826, "e"},   // MA# ( ? �� e ) LATIN SMALL LETTER BLACKLETTER E �� LATIN SMALL LETTER E#
			{43829, "f"},   // MA# ( ? �� f ) LATIN SMALL LETTER LENIS F �� LATIN SMALL LETTER F#
			{43837, "o"},   // MA# ( ? �� o ) LATIN SMALL LETTER BLACKLETTER O �� LATIN SMALL LETTER O#
			{43847, "r"},   // MA# ( ? �� r ) LATIN SMALL LETTER R WITHOUT HANDLE �� LATIN SMALL LETTER R#
			{43848, "r"},   // MA# ( ? �� r ) LATIN SMALL LETTER DOUBLE R �� LATIN SMALL LETTER R#
			{43854, "u"},   // MA# ( ? �� u ) LATIN SMALL LETTER U WITH SHORT RIGHT LEG �� LATIN SMALL LETTER U#
			{43858, "u"},   // MA# ( ? �� u ) LATIN SMALL LETTER U WITH LEFT HOOK �� LATIN SMALL LETTER U#
			{43866, "y"},   // MA# ( ? �� y ) LATIN SMALL LETTER Y WITH SHORT RIGHT LEG �� LATIN SMALL LETTER Y#
			{43875, "uo"},  // MA# ( ? �� uo ) LATIN SMALL LETTER UO �� LATIN SMALL LETTER U, LATIN SMALL LETTER O#
			{43893, "i"},   // MA# ( ? �� i ) CHEROKEE SMALL LETTER V �� LATIN SMALL LETTER I#
			{43905, "r"},   // MA# ( ? �� r ) CHEROKEE SMALL LETTER HU �� LATIN SMALL LETTER R# ��?�����ԡ�
			{43907, "w"},   // MA# ( ? �� w ) CHEROKEE SMALL LETTER LA �� LATIN SMALL LETTER W# ��?��
			{43923, "z"},   // MA# ( ? �� z ) CHEROKEE SMALL LETTER NO �� LATIN SMALL LETTER Z# ��?��
			{43945, "v"},   // MA# ( ? �� v ) CHEROKEE SMALL LETTER DO �� LATIN SMALL LETTER V# ��?��
			{43946, "s"},   // MA# ( ? �� s ) CHEROKEE SMALL LETTER DU �� LATIN SMALL LETTER S# ��?��
			{43951, "c"},   // MA# ( ? �� c ) CHEROKEE SMALL LETTER TLI �� LATIN SMALL LETTER C# ��?��
			{64256, "ff"},  // MA# ( ? �� ff ) LATIN SMALL LIGATURE FF �� LATIN SMALL LETTER F, LATIN SMALL LETTER F#
			{64257, "fi"},  // MA# ( ? �� fi ) LATIN SMALL LIGATURE FI �� LATIN SMALL LETTER F, LATIN SMALL LETTER I#
			{64258, "fl"},  // MA# ( ? �� fl ) LATIN SMALL LIGATURE FL �� LATIN SMALL LETTER F, LATIN SMALL LETTER L#
			{64259, "ffi"}, // MA# ( ? �� ffi ) LATIN SMALL LIGATURE FFI �� LATIN SMALL LETTER F, LATIN SMALL LETTER F, LATIN SMALL LETTER I#
			{64260, "ffl"}, // MA# ( ? �� ffl ) LATIN SMALL LIGATURE FFL �� LATIN SMALL LETTER F, LATIN SMALL LETTER F, LATIN SMALL LETTER L#
			{64262, "st"},  // MA# ( ? �� st ) LATIN SMALL LIGATURE ST �� LATIN SMALL LETTER S, LATIN SMALL LETTER T#
			{64422, "o"},   // MA# ( ??? �� o ) ARABIC LETTER HEH GOAL ISOLATED FORM �� LATIN SMALL LETTER O# ��???��
			{64423, "o"},   // MA# ( ??? �� o ) ARABIC LETTER HEH GOAL FINAL FORM �� LATIN SMALL LETTER O# ��???����???��
			{64424, "o"},   // MA# ( ??? �� o ) ARABIC LETTER HEH GOAL INITIAL FORM �� LATIN SMALL LETTER O# ��???����???��
			{64425, "o"},   // MA# ( ??? �� o ) ARABIC LETTER HEH GOAL MEDIAL FORM �� LATIN SMALL LETTER O# ��???����???��
			{64426, "o"},   // MA# ( ??? �� o ) ARABIC LETTER HEH DOACHASHMEE ISOLATED FORM �� LATIN SMALL LETTER O# ��???��
			{64427, "o"},   // MA# ( ??? �� o ) ARABIC LETTER HEH DOACHASHMEE FINAL FORM �� LATIN SMALL LETTER O# ��???����???��
			{64428, "o"},   // MA# ( ??? �� o ) ARABIC LETTER HEH DOACHASHMEE INITIAL FORM �� LATIN SMALL LETTER O# ��???����???��
			{64429, "o"},   // MA# ( ??? �� o ) ARABIC LETTER HEH DOACHASHMEE MEDIAL FORM �� LATIN SMALL LETTER O# ��???����???��
			{64830, "("},   // MA#* ( ? �� ( ) ORNATE LEFT PARENTHESIS �� LEFT PARENTHESIS#
			{64831, ")"},   // MA#* ( ? �� ) ) ORNATE RIGHT PARENTHESIS �� RIGHT PARENTHESIS#
			{65072, ":"},   // MA#* ( �U �� : ) PRESENTATION FORM FOR VERTICAL TWO DOT LEADER �� COLON#
			{65101, "_"},   // MA# ( �l �� _ ) DASHED LOW LINE �� LOW LINE#
			{65102, "_"},   // MA# ( �m �� _ ) CENTRELINE LOW LINE �� LOW LINE#
			{65103, "_"},   // MA# ( �n �� _ ) WAVY LOW LINE �� LOW LINE#
			{65112, "-"},   // MA#* ( ? �� - ) SMALL EM DASH �� HYPHEN-MINUS#
			{65128, "\\"},  // MA#* ( �� �� \ ) SMALL REVERSE SOLIDUS �� REVERSE SOLIDUS# ��?��
			{65165, "l"},   // MA# ( ??? �� l ) ARABIC LETTER ALEF ISOLATED FORM �� LATIN SMALL LETTER L# ��???����1��
			{65166, "l"},   // MA# ( ??? �� l ) ARABIC LETTER ALEF FINAL FORM �� LATIN SMALL LETTER L# ��???����1��
			{65257, "o"},   // MA# ( ??? �� o ) ARABIC LETTER HEH ISOLATED FORM �� LATIN SMALL LETTER O# ��???��
			{65258, "o"},   // MA# ( ??? �� o ) ARABIC LETTER HEH FINAL FORM �� LATIN SMALL LETTER O# ��???��
			{65259, "o"},   // MA# ( ??? �� o ) ARABIC LETTER HEH INITIAL FORM �� LATIN SMALL LETTER O# ��???��
			{65260, "o"},   // MA# ( ??? �� o ) ARABIC LETTER HEH MEDIAL FORM �� LATIN SMALL LETTER O# ��???��
			{65281, "!"},   // MA#* ( �� �� ! ) FULLWIDTH EXCLAMATION MARK �� EXCLAMATION MARK# ��?��
			{65282, "\""},  // MA#* ( �� �� '' ) FULLWIDTH QUOTATION MARK �� APOSTROPHE, APOSTROPHE# ��������"��# Converted to a quote.
			{65287, "'"},   // MA#* ( �� �� ' ) FULLWIDTH APOSTROPHE �� APOSTROPHE# ������
			{65306, ":"},   // MA#* ( �� �� : ) FULLWIDTH COLON �� COLON# ���U��
			{65313, "A"},   // MA# ( �� �� A ) FULLWIDTH LATIN CAPITAL LETTER A �� LATIN CAPITAL LETTER A# ������
			{65314, "B"},   // MA# ( �� �� B ) FULLWIDTH LATIN CAPITAL LETTER B �� LATIN CAPITAL LETTER B# ������
			{65315, "C"},   // MA# ( �� �� C ) FULLWIDTH LATIN CAPITAL LETTER C �� LATIN CAPITAL LETTER C# ������
			{65317, "E"},   // MA# ( �� �� E ) FULLWIDTH LATIN CAPITAL LETTER E �� LATIN CAPITAL LETTER E# ������
			{65320, "H"},   // MA# ( �� �� H ) FULLWIDTH LATIN CAPITAL LETTER H �� LATIN CAPITAL LETTER H# ������
			{65321, "l"},   // MA# ( �� �� l ) FULLWIDTH LATIN CAPITAL LETTER I �� LATIN SMALL LETTER L# ��?��
			{65322, "J"},   // MA# ( �� �� J ) FULLWIDTH LATIN CAPITAL LETTER J �� LATIN CAPITAL LETTER J# ��?��
			{65323, "K"},   // MA# ( �� �� K ) FULLWIDTH LATIN CAPITAL LETTER K �� LATIN CAPITAL LETTER K# ������
			{65325, "M"},   // MA# ( �� �� M ) FULLWIDTH LATIN CAPITAL LETTER M �� LATIN CAPITAL LETTER M# ������
			{65326, "N"},   // MA# ( �� �� N ) FULLWIDTH LATIN CAPITAL LETTER N �� LATIN CAPITAL LETTER N# ������
			{65327, "O"},   // MA# ( �� �� O ) FULLWIDTH LATIN CAPITAL LETTER O �� LATIN CAPITAL LETTER O# ������
			{65328, "P"},   // MA# ( �� �� P ) FULLWIDTH LATIN CAPITAL LETTER P �� LATIN CAPITAL LETTER P# ������
			{65331, "S"},   // MA# ( �� �� S ) FULLWIDTH LATIN CAPITAL LETTER S �� LATIN CAPITAL LETTER S# ��?��
			{65332, "T"},   // MA# ( �� �� T ) FULLWIDTH LATIN CAPITAL LETTER T �� LATIN CAPITAL LETTER T# ������
			{65336, "X"},   // MA# ( �� �� X ) FULLWIDTH LATIN CAPITAL LETTER X �� LATIN CAPITAL LETTER X# ������
			{65337, "Y"},   // MA# ( �� �� Y ) FULLWIDTH LATIN CAPITAL LETTER Y �� LATIN CAPITAL LETTER Y# ������
			{65338, "Z"},   // MA# ( �� �� Z ) FULLWIDTH LATIN CAPITAL LETTER Z �� LATIN CAPITAL LETTER Z# ������
			{65339, "("},   // MA#* ( �� �� ( ) FULLWIDTH LEFT SQUARE BRACKET �� LEFT PARENTHESIS# ������
			{65340, "\\"},  // MA#* ( �� �� \ ) FULLWIDTH REVERSE SOLIDUS �� REVERSE SOLIDUS# ��?��
			{65341, ")"},   // MA#* ( �� �� ) ) FULLWIDTH RIGHT SQUARE BRACKET �� RIGHT PARENTHESIS# ������
			{65344, "'"},   // MA#* ( �� �� ' ) FULLWIDTH GRAVE ACCENT �� APOSTROPHE# ������
			{65345, "a"},   // MA# ( �� �� a ) FULLWIDTH LATIN SMALL LETTER A �� LATIN SMALL LETTER A# ���ѡ�
			{65347, "c"},   // MA# ( �� �� c ) FULLWIDTH LATIN SMALL LETTER C �� LATIN SMALL LETTER C# �����
			{65349, "e"},   // MA# ( �� �� e ) FULLWIDTH LATIN SMALL LETTER E �� LATIN SMALL LETTER E# ���֡�
			{65351, "g"},   // MA# ( �� �� g ) FULLWIDTH LATIN SMALL LETTER G �� LATIN SMALL LETTER G# ������
			{65352, "h"},   // MA# ( �� �� h ) FULLWIDTH LATIN SMALL LETTER H �� LATIN SMALL LETTER H# ��?��
			{65353, "i"},   // MA# ( �� �� i ) FULLWIDTH LATIN SMALL LETTER I �� LATIN SMALL LETTER I# ��?��
			{65354, "j"},   // MA# ( �� �� j ) FULLWIDTH LATIN SMALL LETTER J �� LATIN SMALL LETTER J# ��?��
			{65356, "l"},   // MA# ( �� �� l ) FULLWIDTH LATIN SMALL LETTER L �� LATIN SMALL LETTER L# �������?��
			{65359, "o"},   // MA# ( �� �� o ) FULLWIDTH LATIN SMALL LETTER O �� LATIN SMALL LETTER O# �����
			{65360, "p"},   // MA# ( �� �� p ) FULLWIDTH LATIN SMALL LETTER P �� LATIN SMALL LETTER P# �����
			{65363, "s"},   // MA# ( �� �� s ) FULLWIDTH LATIN SMALL LETTER S �� LATIN SMALL LETTER S# ��?��
			{65366, "v"},   // MA# ( �� �� v ) FULLWIDTH LATIN SMALL LETTER V �� LATIN SMALL LETTER V# ���͡�
			{65368, "x"},   // MA# ( �� �� x ) FULLWIDTH LATIN SMALL LETTER X �� LATIN SMALL LETTER X# �����
			{65369, "y"},   // MA# ( �� �� y ) FULLWIDTH LATIN SMALL LETTER Y �� LATIN SMALL LETTER Y# �����
			{65512, "l"},   // MA#* ( ? �� l ) HALFWIDTH FORMS LIGHT VERTICAL �� LATIN SMALL LETTER L# ��|��
			{66178, "B"},   // MA# ( ?? �� B ) LYCIAN LETTER B �� LATIN CAPITAL LETTER B#
			{66182, "E"},   // MA# ( ?? �� E ) LYCIAN LETTER I �� LATIN CAPITAL LETTER E#
			{66183, "F"},   // MA# ( ?? �� F ) LYCIAN LETTER W �� LATIN CAPITAL LETTER F#
			{66186, "l"},   // MA# ( ?? �� l ) LYCIAN LETTER J �� LATIN SMALL LETTER L# ��I��
			{66192, "X"},   // MA# ( ?? �� X ) LYCIAN LETTER MM �� LATIN CAPITAL LETTER X#
			{66194, "O"},   // MA# ( ?? �� O ) LYCIAN LETTER U �� LATIN CAPITAL LETTER O#
			{66197, "P"},   // MA# ( ?? �� P ) LYCIAN LETTER R �� LATIN CAPITAL LETTER P#
			{66198, "S"},   // MA# ( ?? �� S ) LYCIAN LETTER S �� LATIN CAPITAL LETTER S#
			{66199, "T"},   // MA# ( ?? �� T ) LYCIAN LETTER T �� LATIN CAPITAL LETTER T#
			{66203, "+"},   // MA# ( ?? �� + ) LYCIAN LETTER H �� PLUS SIGN#
			{66208, "A"},   // MA# ( ?? �� A ) CARIAN LETTER A �� LATIN CAPITAL LETTER A#
			{66209, "B"},   // MA# ( ?? �� B ) CARIAN LETTER P2 �� LATIN CAPITAL LETTER B#
			{66210, "C"},   // MA# ( ?? �� C ) CARIAN LETTER D �� LATIN CAPITAL LETTER C#
			{66213, "F"},   // MA# ( ?? �� F ) CARIAN LETTER R �� LATIN CAPITAL LETTER F#
			{66219, "O"},   // MA# ( ?? �� O ) CARIAN LETTER O �� LATIN CAPITAL LETTER O#
			{66224, "M"},   // MA# ( ?? �� M ) CARIAN LETTER S �� LATIN CAPITAL LETTER M#
			{66225, "T"},   // MA# ( ?? �� T ) CARIAN LETTER C-18 �� LATIN CAPITAL LETTER T#
			{66226, "Y"},   // MA# ( ?? �� Y ) CARIAN LETTER U �� LATIN CAPITAL LETTER Y#
			{66228, "X"},   // MA# ( ?? �� X ) CARIAN LETTER X �� LATIN CAPITAL LETTER X#
			{66255, "H"},   // MA# ( ?? �� H ) CARIAN LETTER E2 �� LATIN CAPITAL LETTER H#
			{66293, "Z"},   // MA#* ( ?? �� Z ) COPTIC EPACT NUMBER THREE HUNDRED �� LATIN CAPITAL LETTER Z#
			{66305, "B"},   // MA# ( ?? �� B ) OLD ITALIC LETTER BE �� LATIN CAPITAL LETTER B#
			{66306, "C"},   // MA# ( ?? �� C ) OLD ITALIC LETTER KE �� LATIN CAPITAL LETTER C#
			{66313, "l"},   // MA# ( ?? �� l ) OLD ITALIC LETTER I �� LATIN SMALL LETTER L# ��I��
			{66321, "M"},   // MA# ( ?? �� M ) OLD ITALIC LETTER SHE �� LATIN CAPITAL LETTER M#
			{66325, "T"},   // MA# ( ?? �� T ) OLD ITALIC LETTER TE �� LATIN CAPITAL LETTER T#
			{66327, "X"},   // MA# ( ?? �� X ) OLD ITALIC LETTER EKS �� LATIN CAPITAL LETTER X#
			{66330, "8"},   // MA# ( ?? �� 8 ) OLD ITALIC LETTER EF �� DIGIT EIGHT#
			{66335, "*"},   // MA# ( ?? �� * ) OLD ITALIC LETTER ESS �� ASTERISK#
			{66336, "l"},   // MA#* ( ?? �� l ) OLD ITALIC NUMERAL ONE �� LATIN SMALL LETTER L# ��??����I��
			{66338, "X"},   // MA#* ( ?? �� X ) OLD ITALIC NUMERAL TEN �� LATIN CAPITAL LETTER X# ��??��
			{66564, "O"},   // MA# ( ?? �� O ) DESERET CAPITAL LETTER LONG O �� LATIN CAPITAL LETTER O#
			{66581, "C"},   // MA# ( ?? �� C ) DESERET CAPITAL LETTER CHEE �� LATIN CAPITAL LETTER C#
			{66587, "L"},   // MA# ( ?? �� L ) DESERET CAPITAL LETTER ETH �� LATIN CAPITAL LETTER L#
			{66592, "S"},   // MA# ( ?? �� S ) DESERET CAPITAL LETTER ZHEE �� LATIN CAPITAL LETTER S#
			{66604, "o"},   // MA# ( ?? �� o ) DESERET SMALL LETTER LONG O �� LATIN SMALL LETTER O#
			{66621, "c"},   // MA# ( ?? �� c ) DESERET SMALL LETTER CHEE �� LATIN SMALL LETTER C#
			{66632, "s"},   // MA# ( ?? �� s ) DESERET SMALL LETTER ZHEE �� LATIN SMALL LETTER S#
			{66740, "R"},   // MA# ( ?? �� R ) OSAGE CAPITAL LETTER BRA �� LATIN CAPITAL LETTER R# ��?��
			{66754, "O"},   // MA# ( ?? �� O ) OSAGE CAPITAL LETTER O �� LATIN CAPITAL LETTER O#
			{66766, "U"},   // MA# ( ?? �� U ) OSAGE CAPITAL LETTER U �� LATIN CAPITAL LETTER U#
			{66770, "7"},   // MA# ( ?? �� 7 ) OSAGE CAPITAL LETTER ZA �� DIGIT SEVEN#
			{66794, "o"},   // MA# ( ?? �� o ) OSAGE SMALL LETTER O �� LATIN SMALL LETTER O#
			{66806, "u"},   // MA# ( ?? �� u ) OSAGE SMALL LETTER U �� LATIN SMALL LETTER U# ��?��
			{66835, "N"},   // MA# ( ?? �� N ) ELBASAN LETTER NE �� LATIN CAPITAL LETTER N#
			{66838, "O"},   // MA# ( ?? �� O ) ELBASAN LETTER O �� LATIN CAPITAL LETTER O#
			{66840, "K"},   // MA# ( ?? �� K ) ELBASAN LETTER QE �� LATIN CAPITAL LETTER K#
			{66844, "C"},   // MA# ( ?? �� C ) ELBASAN LETTER SHE �� LATIN CAPITAL LETTER C#
			{66845, "V"},   // MA# ( ?? �� V ) ELBASAN LETTER TE �� LATIN CAPITAL LETTER V#
			{66853, "F"},   // MA# ( ?? �� F ) ELBASAN LETTER GHE �� LATIN CAPITAL LETTER F#
			{66854, "L"},   // MA# ( ?? �� L ) ELBASAN LETTER GHAMMA �� LATIN CAPITAL LETTER L#
			{66855, "X"},   // MA# ( ?? �� X ) ELBASAN LETTER KHE �� LATIN CAPITAL LETTER X#
			{68176, "."},   // MA#* ( ???? �� . ) KHAROSHTHI PUNCTUATION DOT �� FULL STOP#
			{70864, "O"},   // MA# ( ?? �� O ) TIRHUTA DIGIT ZERO �� LATIN CAPITAL LETTER O# ��?����0��
			{71424, "rn"},  // MA# ( ?? �� rn ) AHOM LETTER KA �� LATIN SMALL LETTER R, LATIN SMALL LETTER N# ��m��
			{71430, "v"},   // MA# ( ?? �� v ) AHOM LETTER PA �� LATIN SMALL LETTER V#
			{71434, "w"},   // MA# ( ?? �� w ) AHOM LETTER JA �� LATIN SMALL LETTER W#
			{71438, "w"},   // MA# ( ?? �� w ) AHOM LETTER LA �� LATIN SMALL LETTER W#
			{71439, "w"},   // MA# ( ?? �� w ) AHOM LETTER SA �� LATIN SMALL LETTER W#
			{71840, "V"},   // MA# ( ?? �� V ) WARANG CITI CAPITAL LETTER NGAA �� LATIN CAPITAL LETTER V#
			{71842, "F"},   // MA# ( ?? �� F ) WARANG CITI CAPITAL LETTER WI �� LATIN CAPITAL LETTER F#
			{71843, "L"},   // MA# ( ?? �� L ) WARANG CITI CAPITAL LETTER YU �� LATIN CAPITAL LETTER L#
			{71844, "Y"},   // MA# ( ?? �� Y ) WARANG CITI CAPITAL LETTER YA �� LATIN CAPITAL LETTER Y#
			{71846, "E"},   // MA# ( ?? �� E ) WARANG CITI CAPITAL LETTER II �� LATIN CAPITAL LETTER E#
			{71849, "Z"},   // MA# ( ?? �� Z ) WARANG CITI CAPITAL LETTER O �� LATIN CAPITAL LETTER Z#
			{71852, "9"},   // MA# ( ?? �� 9 ) WARANG CITI CAPITAL LETTER KO �� DIGIT NINE#
			{71854, "E"},   // MA# ( ?? �� E ) WARANG CITI CAPITAL LETTER YUJ �� LATIN CAPITAL LETTER E#
			{71855, "4"},   // MA# ( ?? �� 4 ) WARANG CITI CAPITAL LETTER UC �� DIGIT FOUR#
			{71858, "L"},   // MA# ( ?? �� L ) WARANG CITI CAPITAL LETTER TTE �� LATIN CAPITAL LETTER L#
			{71861, "O"},   // MA# ( ?? �� O ) WARANG CITI CAPITAL LETTER AT �� LATIN CAPITAL LETTER O#
			{71864, "U"},   // MA# ( ?? �� U ) WARANG CITI CAPITAL LETTER PU �� LATIN CAPITAL LETTER U#
			{71867, "5"},   // MA# ( ?? �� 5 ) WARANG CITI CAPITAL LETTER HORR �� DIGIT FIVE#
			{71868, "T"},   // MA# ( ?? �� T ) WARANG CITI CAPITAL LETTER HAR �� LATIN CAPITAL LETTER T#
			{71872, "v"},   // MA# ( ?? �� v ) WARANG CITI SMALL LETTER NGAA �� LATIN SMALL LETTER V#
			{71873, "s"},   // MA# ( ?? �� s ) WARANG CITI SMALL LETTER A �� LATIN SMALL LETTER S#
			{71874, "F"},   // MA# ( ?? �� F ) WARANG CITI SMALL LETTER WI �� LATIN CAPITAL LETTER F#
			{71875, "i"},   // MA# ( ?? �� i ) WARANG CITI SMALL LETTER YU �� LATIN SMALL LETTER I# ���ɡ�
			{71876, "z"},   // MA# ( ?? �� z ) WARANG CITI SMALL LETTER YA �� LATIN SMALL LETTER Z#
			{71878, "7"},   // MA# ( ?? �� 7 ) WARANG CITI SMALL LETTER II �� DIGIT SEVEN#
			{71880, "o"},   // MA# ( ?? �� o ) WARANG CITI SMALL LETTER E �� LATIN SMALL LETTER O#
			{71882, "3"},   // MA# ( ?? �� 3 ) WARANG CITI SMALL LETTER ANG �� DIGIT THREE#
			{71884, "9"},   // MA# ( ?? �� 9 ) WARANG CITI SMALL LETTER KO �� DIGIT NINE#
			{71893, "6"},   // MA# ( ?? �� 6 ) WARANG CITI SMALL LETTER AT �� DIGIT SIX#
			{71894, "9"},   // MA# ( ?? �� 9 ) WARANG CITI SMALL LETTER AM �� DIGIT NINE#
			{71895, "o"},   // MA# ( ?? �� o ) WARANG CITI SMALL LETTER BU �� LATIN SMALL LETTER O#
			{71896, "u"},   // MA# ( ?? �� u ) WARANG CITI SMALL LETTER PU �� LATIN SMALL LETTER U# ���ԡ���?��
			{71900, "y"},   // MA# ( ?? �� y ) WARANG CITI SMALL LETTER HAR �� LATIN SMALL LETTER Y# ��?�����á�
			{71904, "O"},   // MA# ( ?? �� O ) WARANG CITI DIGIT ZERO �� LATIN CAPITAL LETTER O# ��0��
			{71907, "rn"},  // MA# ( ?? �� rn ) WARANG CITI DIGIT THREE �� LATIN SMALL LETTER R, LATIN SMALL LETTER N# ��m��
			{71909, "Z"},   // MA# ( ?? �� Z ) WARANG CITI DIGIT FIVE �� LATIN CAPITAL LETTER Z#
			{71910, "W"},   // MA# ( ?? �� W ) WARANG CITI DIGIT SIX �� LATIN CAPITAL LETTER W#
			{71913, "C"},   // MA# ( ?? �� C ) WARANG CITI DIGIT NINE �� LATIN CAPITAL LETTER C#
			{71916, "X"},   // MA#* ( ?? �� X ) WARANG CITI NUMBER THIRTY �� LATIN CAPITAL LETTER X#
			{71919, "W"},   // MA#* ( ?? �� W ) WARANG CITI NUMBER SIXTY �� LATIN CAPITAL LETTER W#
			{71922, "C"},   // MA#* ( ?? �� C ) WARANG CITI NUMBER NINETY �� LATIN CAPITAL LETTER C#
			{93960, "V"},   // MA# ( ?? �� V ) MIAO LETTER VA �� LATIN CAPITAL LETTER V#
			{93962, "T"},   // MA# ( ?? �� T ) MIAO LETTER TA �� LATIN CAPITAL LETTER T#
			{93974, "L"},   // MA# ( ?? �� L ) MIAO LETTER LA �� LATIN CAPITAL LETTER L#
			{93992, "l"},   // MA# ( ?? �� l ) MIAO LETTER GHA �� LATIN SMALL LETTER L# ��I��
			{94005, "R"},   // MA# ( ?? �� R ) MIAO LETTER ZHA �� LATIN CAPITAL LETTER R#
			{94010, "S"},   // MA# ( ?? �� S ) MIAO LETTER SA �� LATIN CAPITAL LETTER S#
			{94011, "3"},   // MA# ( ?? �� 3 ) MIAO LETTER ZA �� DIGIT THREE# ��?��
			{94015, ">"},   // MA# ( ?? �� > ) MIAO LETTER ARCHAIC ZZA �� GREATER-THAN SIGN#
			{94016, "A"},   // MA# ( ?? �� A ) MIAO LETTER ZZYA �� LATIN CAPITAL LETTER A#
			{94018, "U"},   // MA# ( ?? �� U ) MIAO LETTER WA �� LATIN CAPITAL LETTER U#
			{94019, "Y"},   // MA# ( ?? �� Y ) MIAO LETTER AH �� LATIN CAPITAL LETTER Y#
			{94033, "'"},   // MA# ( ?? �� ' ) MIAO SIGN ASPIRATION �� APOSTROPHE# ��?�������
			{94034, "'"},   // MA# ( ?? �� ' ) MIAO SIGN REFORMED VOICING �� APOSTROPHE# ��?��������
			{119060, "{"},  // MA#* ( ?? �� { ) MUSICAL SYMBOL BRACE �� LEFT CURLY BRACKET#
			{119149, "."},  // MA# ( ?? �� . ) MUSICAL SYMBOL COMBINING AUGMENTATION DOT �� FULL STOP#
			{119302, "3"},  // MA#* ( ?? �� 3 ) GREEK VOCAL NOTATION SYMBOL-7 �� DIGIT THREE#
			{119309, "V"},  // MA#* ( ?? �� V ) GREEK VOCAL NOTATION SYMBOL-14 �� LATIN CAPITAL LETTER V#
			{119311, "\\"}, // MA#* ( ?? �� \ ) GREEK VOCAL NOTATION SYMBOL-16 �� REVERSE SOLIDUS#
			{119314, "7"},  // MA#* ( ?? �� 7 ) GREEK VOCAL NOTATION SYMBOL-19 �� DIGIT SEVEN#
			{119315, "F"},  // MA#* ( ?? �� F ) GREEK VOCAL NOTATION SYMBOL-20 �� LATIN CAPITAL LETTER F# ��?��
			{119318, "R"},  // MA#* ( ?? �� R ) GREEK VOCAL NOTATION SYMBOL-23 �� LATIN CAPITAL LETTER R#
			{119338, "L"},  // MA#* ( ?? �� L ) GREEK INSTRUMENTAL NOTATION SYMBOL-23 �� LATIN CAPITAL LETTER L#
			{119350, "<"},  // MA#* ( ?? �� < ) GREEK INSTRUMENTAL NOTATION SYMBOL-40 �� LESS-THAN SIGN#
			{119351, ">"},  // MA#* ( ?? �� > ) GREEK INSTRUMENTAL NOTATION SYMBOL-42 �� GREATER-THAN SIGN#
			{119354, "/"},  // MA#* ( ?? �� / ) GREEK INSTRUMENTAL NOTATION SYMBOL-47 �� SOLIDUS#
			{119355, "\\"}, // MA#* ( ?? �� \ ) GREEK INSTRUMENTAL NOTATION SYMBOL-48 �� REVERSE SOLIDUS# ��??��
			{119808, "A"},  // MA# ( ?? �� A ) MATHEMATICAL BOLD CAPITAL A �� LATIN CAPITAL LETTER A#
			{119809, "B"},  // MA# ( ?? �� B ) MATHEMATICAL BOLD CAPITAL B �� LATIN CAPITAL LETTER B#
			{119810, "C"},  // MA# ( ?? �� C ) MATHEMATICAL BOLD CAPITAL C �� LATIN CAPITAL LETTER C#
			{119811, "D"},  // MA# ( ?? �� D ) MATHEMATICAL BOLD CAPITAL D �� LATIN CAPITAL LETTER D#
			{119812, "E"},  // MA# ( ?? �� E ) MATHEMATICAL BOLD CAPITAL E �� LATIN CAPITAL LETTER E#
			{119813, "F"},  // MA# ( ?? �� F ) MATHEMATICAL BOLD CAPITAL F �� LATIN CAPITAL LETTER F#
			{119814, "G"},  // MA# ( ?? �� G ) MATHEMATICAL BOLD CAPITAL G �� LATIN CAPITAL LETTER G#
			{119815, "H"},  // MA# ( ?? �� H ) MATHEMATICAL BOLD CAPITAL H �� LATIN CAPITAL LETTER H#
			{119816, "l"},  // MA# ( ?? �� l ) MATHEMATICAL BOLD CAPITAL I �� LATIN SMALL LETTER L# ��I��
			{119817, "J"},  // MA# ( ?? �� J ) MATHEMATICAL BOLD CAPITAL J �� LATIN CAPITAL LETTER J#
			{119818, "K"},  // MA# ( ?? �� K ) MATHEMATICAL BOLD CAPITAL K �� LATIN CAPITAL LETTER K#
			{119819, "L"},  // MA# ( ?? �� L ) MATHEMATICAL BOLD CAPITAL L �� LATIN CAPITAL LETTER L#
			{119820, "M"},  // MA# ( ?? �� M ) MATHEMATICAL BOLD CAPITAL M �� LATIN CAPITAL LETTER M#
			{119821, "N"},  // MA# ( ?? �� N ) MATHEMATICAL BOLD CAPITAL N �� LATIN CAPITAL LETTER N#
			{119822, "O"},  // MA# ( ?? �� O ) MATHEMATICAL BOLD CAPITAL O �� LATIN CAPITAL LETTER O#
			{119823, "P"},  // MA# ( ?? �� P ) MATHEMATICAL BOLD CAPITAL P �� LATIN CAPITAL LETTER P#
			{119824, "Q"},  // MA# ( ?? �� Q ) MATHEMATICAL BOLD CAPITAL Q �� LATIN CAPITAL LETTER Q#
			{119825, "R"},  // MA# ( ?? �� R ) MATHEMATICAL BOLD CAPITAL R �� LATIN CAPITAL LETTER R#
			{119826, "S"},  // MA# ( ?? �� S ) MATHEMATICAL BOLD CAPITAL S �� LATIN CAPITAL LETTER S#
			{119827, "T"},  // MA# ( ?? �� T ) MATHEMATICAL BOLD CAPITAL T �� LATIN CAPITAL LETTER T#
			{119828, "U"},  // MA# ( ?? �� U ) MATHEMATICAL BOLD CAPITAL U �� LATIN CAPITAL LETTER U#
			{119829, "V"},  // MA# ( ?? �� V ) MATHEMATICAL BOLD CAPITAL V �� LATIN CAPITAL LETTER V#
			{119830, "W"},  // MA# ( ?? �� W ) MATHEMATICAL BOLD CAPITAL W �� LATIN CAPITAL LETTER W#
			{119831, "X"},  // MA# ( ?? �� X ) MATHEMATICAL BOLD CAPITAL X �� LATIN CAPITAL LETTER X#
			{119832, "Y"},  // MA# ( ?? �� Y ) MATHEMATICAL BOLD CAPITAL Y �� LATIN CAPITAL LETTER Y#
			{119833, "Z"},  // MA# ( ?? �� Z ) MATHEMATICAL BOLD CAPITAL Z �� LATIN CAPITAL LETTER Z#
			{119834, "a"},  // MA# ( ?? �� a ) MATHEMATICAL BOLD SMALL A �� LATIN SMALL LETTER A#
			{119835, "b"},  // MA# ( ?? �� b ) MATHEMATICAL BOLD SMALL B �� LATIN SMALL LETTER B#
			{119836, "c"},  // MA# ( ?? �� c ) MATHEMATICAL BOLD SMALL C �� LATIN SMALL LETTER C#
			{119837, "d"},  // MA# ( ?? �� d ) MATHEMATICAL BOLD SMALL D �� LATIN SMALL LETTER D#
			{119838, "e"},  // MA# ( ?? �� e ) MATHEMATICAL BOLD SMALL E �� LATIN SMALL LETTER E#
			{119839, "f"},  // MA# ( ?? �� f ) MATHEMATICAL BOLD SMALL F �� LATIN SMALL LETTER F#
			{119840, "g"},  // MA# ( ?? �� g ) MATHEMATICAL BOLD SMALL G �� LATIN SMALL LETTER G#
			{119841, "h"},  // MA# ( ?? �� h ) MATHEMATICAL BOLD SMALL H �� LATIN SMALL LETTER H#
			{119842, "i"},  // MA# ( ?? �� i ) MATHEMATICAL BOLD SMALL I �� LATIN SMALL LETTER I#
			{119843, "j"},  // MA# ( ?? �� j ) MATHEMATICAL BOLD SMALL J �� LATIN SMALL LETTER J#
			{119844, "k"},  // MA# ( ?? �� k ) MATHEMATICAL BOLD SMALL K �� LATIN SMALL LETTER K#
			{119845, "l"},  // MA# ( ?? �� l ) MATHEMATICAL BOLD SMALL L �� LATIN SMALL LETTER L#
			{119846, "rn"}, // MA# ( ?? �� rn ) MATHEMATICAL BOLD SMALL M �� LATIN SMALL LETTER R, LATIN SMALL LETTER N# ��m��
			{119847, "n"},  // MA# ( ?? �� n ) MATHEMATICAL BOLD SMALL N �� LATIN SMALL LETTER N#
			{119848, "o"},  // MA# ( ?? �� o ) MATHEMATICAL BOLD SMALL O �� LATIN SMALL LETTER O#
			{119849, "p"},  // MA# ( ?? �� p ) MATHEMATICAL BOLD SMALL P �� LATIN SMALL LETTER P#
			{119850, "q"},  // MA# ( ?? �� q ) MATHEMATICAL BOLD SMALL Q �� LATIN SMALL LETTER Q#
			{119851, "r"},  // MA# ( ?? �� r ) MATHEMATICAL BOLD SMALL R �� LATIN SMALL LETTER R#
			{119852, "s"},  // MA# ( ?? �� s ) MATHEMATICAL BOLD SMALL S �� LATIN SMALL LETTER S#
			{119853, "t"},  // MA# ( ?? �� t ) MATHEMATICAL BOLD SMALL T �� LATIN SMALL LETTER T#
			{119854, "u"},  // MA# ( ?? �� u ) MATHEMATICAL BOLD SMALL U �� LATIN SMALL LETTER U#
			{119855, "v"},  // MA# ( ?? �� v ) MATHEMATICAL BOLD SMALL V �� LATIN SMALL LETTER V#
			{119856, "w"},  // MA# ( ?? �� w ) MATHEMATICAL BOLD SMALL W �� LATIN SMALL LETTER W#
			{119857, "x"},  // MA# ( ?? �� x ) MATHEMATICAL BOLD SMALL X �� LATIN SMALL LETTER X#
			{119858, "y"},  // MA# ( ?? �� y ) MATHEMATICAL BOLD SMALL Y �� LATIN SMALL LETTER Y#
			{119859, "z"},  // MA# ( ?? �� z ) MATHEMATICAL BOLD SMALL Z �� LATIN SMALL LETTER Z#
			{119860, "A"},  // MA# ( ?? �� A ) MATHEMATICAL ITALIC CAPITAL A �� LATIN CAPITAL LETTER A#
			{119861, "B"},  // MA# ( ?? �� B ) MATHEMATICAL ITALIC CAPITAL B �� LATIN CAPITAL LETTER B#
			{119862, "C"},  // MA# ( ?? �� C ) MATHEMATICAL ITALIC CAPITAL C �� LATIN CAPITAL LETTER C#
			{119863, "D"},  // MA# ( ?? �� D ) MATHEMATICAL ITALIC CAPITAL D �� LATIN CAPITAL LETTER D#
			{119864, "E"},  // MA# ( ?? �� E ) MATHEMATICAL ITALIC CAPITAL E �� LATIN CAPITAL LETTER E#
			{119865, "F"},  // MA# ( ?? �� F ) MATHEMATICAL ITALIC CAPITAL F �� LATIN CAPITAL LETTER F#
			{119866, "G"},  // MA# ( ?? �� G ) MATHEMATICAL ITALIC CAPITAL G �� LATIN CAPITAL LETTER G#
			{119867, "H"},  // MA# ( ?? �� H ) MATHEMATICAL ITALIC CAPITAL H �� LATIN CAPITAL LETTER H#
			{119868, "l"},  // MA# ( ?? �� l ) MATHEMATICAL ITALIC CAPITAL I �� LATIN SMALL LETTER L# ��I��
			{119869, "J"},  // MA# ( ?? �� J ) MATHEMATICAL ITALIC CAPITAL J �� LATIN CAPITAL LETTER J#
			{119870, "K"},  // MA# ( ?? �� K ) MATHEMATICAL ITALIC CAPITAL K �� LATIN CAPITAL LETTER K#
			{119871, "L"},  // MA# ( ?? �� L ) MATHEMATICAL ITALIC CAPITAL L �� LATIN CAPITAL LETTER L#
			{119872, "M"},  // MA# ( ?? �� M ) MATHEMATICAL ITALIC CAPITAL M �� LATIN CAPITAL LETTER M#
			{119873, "N"},  // MA# ( ?? �� N ) MATHEMATICAL ITALIC CAPITAL N �� LATIN CAPITAL LETTER N#
			{119874, "O"},  // MA# ( ?? �� O ) MATHEMATICAL ITALIC CAPITAL O �� LATIN CAPITAL LETTER O#
			{119875, "P"},  // MA# ( ?? �� P ) MATHEMATICAL ITALIC CAPITAL P �� LATIN CAPITAL LETTER P#
			{119876, "Q"},  // MA# ( ?? �� Q ) MATHEMATICAL ITALIC CAPITAL Q �� LATIN CAPITAL LETTER Q#
			{119877, "R"},  // MA# ( ?? �� R ) MATHEMATICAL ITALIC CAPITAL R �� LATIN CAPITAL LETTER R#
			{119878, "S"},  // MA# ( ?? �� S ) MATHEMATICAL ITALIC CAPITAL S �� LATIN CAPITAL LETTER S#
			{119879, "T"},  // MA# ( ?? �� T ) MATHEMATICAL ITALIC CAPITAL T �� LATIN CAPITAL LETTER T#
			{119880, "U"},  // MA# ( ?? �� U ) MATHEMATICAL ITALIC CAPITAL U �� LATIN CAPITAL LETTER U#
			{119881, "V"},  // MA# ( ?? �� V ) MATHEMATICAL ITALIC CAPITAL V �� LATIN CAPITAL LETTER V#
			{119882, "W"},  // MA# ( ?? �� W ) MATHEMATICAL ITALIC CAPITAL W �� LATIN CAPITAL LETTER W#
			{119883, "X"},  // MA# ( ?? �� X ) MATHEMATICAL ITALIC CAPITAL X �� LATIN CAPITAL LETTER X#
			{119884, "Y"},  // MA# ( ?? �� Y ) MATHEMATICAL ITALIC CAPITAL Y �� LATIN CAPITAL LETTER Y#
			{119885, "Z"},  // MA# ( ?? �� Z ) MATHEMATICAL ITALIC CAPITAL Z �� LATIN CAPITAL LETTER Z#
			{119886, "a"},  // MA# ( ?? �� a ) MATHEMATICAL ITALIC SMALL A �� LATIN SMALL LETTER A#
			{119887, "b"},  // MA# ( ?? �� b ) MATHEMATICAL ITALIC SMALL B �� LATIN SMALL LETTER B#
			{119888, "c"},  // MA# ( ?? �� c ) MATHEMATICAL ITALIC SMALL C �� LATIN SMALL LETTER C#
			{119889, "d"},  // MA# ( ?? �� d ) MATHEMATICAL ITALIC SMALL D �� LATIN SMALL LETTER D#
			{119890, "e"},  // MA# ( ?? �� e ) MATHEMATICAL ITALIC SMALL E �� LATIN SMALL LETTER E#
			{119891, "f"},  // MA# ( ?? �� f ) MATHEMATICAL ITALIC SMALL F �� LATIN SMALL LETTER F#
			{119892, "g"},  // MA# ( ?? �� g ) MATHEMATICAL ITALIC SMALL G �� LATIN SMALL LETTER G#
			{119894, "i"},  // MA# ( ?? �� i ) MATHEMATICAL ITALIC SMALL I �� LATIN SMALL LETTER I#
			{119895, "j"},  // MA# ( ?? �� j ) MATHEMATICAL ITALIC SMALL J �� LATIN SMALL LETTER J#
			{119896, "k"},  // MA# ( ?? �� k ) MATHEMATICAL ITALIC SMALL K �� LATIN SMALL LETTER K#
			{119897, "l"},  // MA# ( ?? �� l ) MATHEMATICAL ITALIC SMALL L �� LATIN SMALL LETTER L#
			{119898, "rn"}, // MA# ( ?? �� rn ) MATHEMATICAL ITALIC SMALL M �� LATIN SMALL LETTER R, LATIN SMALL LETTER N# ��m��
			{119899, "n"},  // MA# ( ?? �� n ) MATHEMATICAL ITALIC SMALL N �� LATIN SMALL LETTER N#
			{119900, "o"},  // MA# ( ?? �� o ) MATHEMATICAL ITALIC SMALL O �� LATIN SMALL LETTER O#
			{119901, "p"},  // MA# ( ?? �� p ) MATHEMATICAL ITALIC SMALL P �� LATIN SMALL LETTER P#
			{119902, "q"},  // MA# ( ?? �� q ) MATHEMATICAL ITALIC SMALL Q �� LATIN SMALL LETTER Q#
			{119903, "r"},  // MA# ( ?? �� r ) MATHEMATICAL ITALIC SMALL R �� LATIN SMALL LETTER R#
			{119904, "s"},  // MA# ( ?? �� s ) MATHEMATICAL ITALIC SMALL S �� LATIN SMALL LETTER S#
			{119905, "t"},  // MA# ( ?? �� t ) MATHEMATICAL ITALIC SMALL T �� LATIN SMALL LETTER T#
			{119906, "u"},  // MA# ( ?? �� u ) MATHEMATICAL ITALIC SMALL U �� LATIN SMALL LETTER U#
			{119907, "v"},  // MA# ( ?? �� v ) MATHEMATICAL ITALIC SMALL V �� LATIN SMALL LETTER V#
			{119908, "w"},  // MA# ( ?? �� w ) MATHEMATICAL ITALIC SMALL W �� LATIN SMALL LETTER W#
			{119909, "x"},  // MA# ( ?? �� x ) MATHEMATICAL ITALIC SMALL X �� LATIN SMALL LETTER X#
			{119910, "y"},  // MA# ( ?? �� y ) MATHEMATICAL ITALIC SMALL Y �� LATIN SMALL LETTER Y#
			{119911, "z"},  // MA# ( ?? �� z ) MATHEMATICAL ITALIC SMALL Z �� LATIN SMALL LETTER Z#
			{119912, "A"},  // MA# ( ?? �� A ) MATHEMATICAL BOLD ITALIC CAPITAL A �� LATIN CAPITAL LETTER A#
			{119913, "B"},  // MA# ( ?? �� B ) MATHEMATICAL BOLD ITALIC CAPITAL B �� LATIN CAPITAL LETTER B#
			{119914, "C"},  // MA# ( ?? �� C ) MATHEMATICAL BOLD ITALIC CAPITAL C �� LATIN CAPITAL LETTER C#
			{119915, "D"},  // MA# ( ?? �� D ) MATHEMATICAL BOLD ITALIC CAPITAL D �� LATIN CAPITAL LETTER D#
			{119916, "E"},  // MA# ( ?? �� E ) MATHEMATICAL BOLD ITALIC CAPITAL E �� LATIN CAPITAL LETTER E#
			{119917, "F"},  // MA# ( ?? �� F ) MATHEMATICAL BOLD ITALIC CAPITAL F �� LATIN CAPITAL LETTER F#
			{119918, "G"},  // MA# ( ?? �� G ) MATHEMATICAL BOLD ITALIC CAPITAL G �� LATIN CAPITAL LETTER G#
			{119919, "H"},  // MA# ( ?? �� H ) MATHEMATICAL BOLD ITALIC CAPITAL H �� LATIN CAPITAL LETTER H#
			{119920, "l"},  // MA# ( ?? �� l ) MATHEMATICAL BOLD ITALIC CAPITAL I �� LATIN SMALL LETTER L# ��I��
			{119921, "J"},  // MA# ( ?? �� J ) MATHEMATICAL BOLD ITALIC CAPITAL J �� LATIN CAPITAL LETTER J#
			{119922, "K"},  // MA# ( ?? �� K ) MATHEMATICAL BOLD ITALIC CAPITAL K �� LATIN CAPITAL LETTER K#
			{119923, "L"},  // MA# ( ?? �� L ) MATHEMATICAL BOLD ITALIC CAPITAL L �� LATIN CAPITAL LETTER L#
			{119924, "M"},  // MA# ( ?? �� M ) MATHEMATICAL BOLD ITALIC CAPITAL M �� LATIN CAPITAL LETTER M#
			{119925, "N"},  // MA# ( ?? �� N ) MATHEMATICAL BOLD ITALIC CAPITAL N �� LATIN CAPITAL LETTER N#
			{119926, "O"},  // MA# ( ?? �� O ) MATHEMATICAL BOLD ITALIC CAPITAL O �� LATIN CAPITAL LETTER O#
			{119927, "P"},  // MA# ( ?? �� P ) MATHEMATICAL BOLD ITALIC CAPITAL P �� LATIN CAPITAL LETTER P#
			{119928, "Q"},  // MA# ( ?? �� Q ) MATHEMATICAL BOLD ITALIC CAPITAL Q �� LATIN CAPITAL LETTER Q#
			{119929, "R"},  // MA# ( ?? �� R ) MATHEMATICAL BOLD ITALIC CAPITAL R �� LATIN CAPITAL LETTER R#
			{119930, "S"},  // MA# ( ?? �� S ) MATHEMATICAL BOLD ITALIC CAPITAL S �� LATIN CAPITAL LETTER S#
			{119931, "T"},  // MA# ( ?? �� T ) MATHEMATICAL BOLD ITALIC CAPITAL T �� LATIN CAPITAL LETTER T#
			{119932, "U"},  // MA# ( ?? �� U ) MATHEMATICAL BOLD ITALIC CAPITAL U �� LATIN CAPITAL LETTER U#
			{119933, "V"},  // MA# ( ?? �� V ) MATHEMATICAL BOLD ITALIC CAPITAL V �� LATIN CAPITAL LETTER V#
			{119934, "W"},  // MA# ( ?? �� W ) MATHEMATICAL BOLD ITALIC CAPITAL W �� LATIN CAPITAL LETTER W#
			{119935, "X"},  // MA# ( ?? �� X ) MATHEMATICAL BOLD ITALIC CAPITAL X �� LATIN CAPITAL LETTER X#
			{119936, "Y"},  // MA# ( ?? �� Y ) MATHEMATICAL BOLD ITALIC CAPITAL Y �� LATIN CAPITAL LETTER Y#
			{119937, "Z"},  // MA# ( ?? �� Z ) MATHEMATICAL BOLD ITALIC CAPITAL Z �� LATIN CAPITAL LETTER Z#
			{119938, "a"},  // MA# ( ?? �� a ) MATHEMATICAL BOLD ITALIC SMALL A �� LATIN SMALL LETTER A#
			{119939, "b"},  // MA# ( ?? �� b ) MATHEMATICAL BOLD ITALIC SMALL B �� LATIN SMALL LETTER B#
			{119940, "c"},  // MA# ( ?? �� c ) MATHEMATICAL BOLD ITALIC SMALL C �� LATIN SMALL LETTER C#
			{119941, "d"},  // MA# ( ?? �� d ) MATHEMATICAL BOLD ITALIC SMALL D �� LATIN SMALL LETTER D#
			{119942, "e"},  // MA# ( ?? �� e ) MATHEMATICAL BOLD ITALIC SMALL E �� LATIN SMALL LETTER E#
			{119943, "f"},  // MA# ( ?? �� f ) MATHEMATICAL BOLD ITALIC SMALL F �� LATIN SMALL LETTER F#
			{119944, "g"},  // MA# ( ?? �� g ) MATHEMATICAL BOLD ITALIC SMALL G �� LATIN SMALL LETTER G#
			{119945, "h"},  // MA# ( ?? �� h ) MATHEMATICAL BOLD ITALIC SMALL H �� LATIN SMALL LETTER H#
			{119946, "i"},  // MA# ( ?? �� i ) MATHEMATICAL BOLD ITALIC SMALL I �� LATIN SMALL LETTER I#
			{119947, "j"},  // MA# ( ?? �� j ) MATHEMATICAL BOLD ITALIC SMALL J �� LATIN SMALL LETTER J#
			{119948, "k"},  // MA# ( ?? �� k ) MATHEMATICAL BOLD ITALIC SMALL K �� LATIN SMALL LETTER K#
			{119949, "l"},  // MA# ( ?? �� l ) MATHEMATICAL BOLD ITALIC SMALL L �� LATIN SMALL LETTER L#
			{119950, "rn"}, // MA# ( ?? �� rn ) MATHEMATICAL BOLD ITALIC SMALL M �� LATIN SMALL LETTER R, LATIN SMALL LETTER N# ��m��
			{119951, "n"},  // MA# ( ?? �� n ) MATHEMATICAL BOLD ITALIC SMALL N �� LATIN SMALL LETTER N#
			{119952, "o"},  // MA# ( ?? �� o ) MATHEMATICAL BOLD ITALIC SMALL O �� LATIN SMALL LETTER O#
			{119953, "p"},  // MA# ( ?? �� p ) MATHEMATICAL BOLD ITALIC SMALL P �� LATIN SMALL LETTER P#
			{119954, "q"},  // MA# ( ?? �� q ) MATHEMATICAL BOLD ITALIC SMALL Q �� LATIN SMALL LETTER Q#
			{119955, "r"},  // MA# ( ?? �� r ) MATHEMATICAL BOLD ITALIC SMALL R �� LATIN SMALL LETTER R#
			{119956, "s"},  // MA# ( ?? �� s ) MATHEMATICAL BOLD ITALIC SMALL S �� LATIN SMALL LETTER S#
			{119957, "t"},  // MA# ( ?? �� t ) MATHEMATICAL BOLD ITALIC SMALL T �� LATIN SMALL LETTER T#
			{119958, "u"},  // MA# ( ?? �� u ) MATHEMATICAL BOLD ITALIC SMALL U �� LATIN SMALL LETTER U#
			{119959, "v"},  // MA# ( ?? �� v ) MATHEMATICAL BOLD ITALIC SMALL V �� LATIN SMALL LETTER V#
			{119960, "w"},  // MA# ( ?? �� w ) MATHEMATICAL BOLD ITALIC SMALL W �� LATIN SMALL LETTER W#
			{119961, "x"},  // MA# ( ?? �� x ) MATHEMATICAL BOLD ITALIC SMALL X �� LATIN SMALL LETTER X#
			{119962, "y"},  // MA# ( ?? �� y ) MATHEMATICAL BOLD ITALIC SMALL Y �� LATIN SMALL LETTER Y#
			{119963, "z"},  // MA# ( ?? �� z ) MATHEMATICAL BOLD ITALIC SMALL Z �� LATIN SMALL LETTER Z#
			{119964, "A"},  // MA# ( ?? �� A ) MATHEMATICAL SCRIPT CAPITAL A �� LATIN CAPITAL LETTER A#
			{119966, "C"},  // MA# ( ?? �� C ) MATHEMATICAL SCRIPT CAPITAL C �� LATIN CAPITAL LETTER C#
			{119967, "D"},  // MA# ( ?? �� D ) MATHEMATICAL SCRIPT CAPITAL D �� LATIN CAPITAL LETTER D#
			{119970, "G"},  // MA# ( ?? �� G ) MATHEMATICAL SCRIPT CAPITAL G �� LATIN CAPITAL LETTER G#
			{119973, "J"},  // MA# ( ?? �� J ) MATHEMATICAL SCRIPT CAPITAL J �� LATIN CAPITAL LETTER J#
			{119974, "K"},  // MA# ( ?? �� K ) MATHEMATICAL SCRIPT CAPITAL K �� LATIN CAPITAL LETTER K#
			{119977, "N"},  // MA# ( ?? �� N ) MATHEMATICAL SCRIPT CAPITAL N �� LATIN CAPITAL LETTER N#
			{119978, "O"},  // MA# ( ?? �� O ) MATHEMATICAL SCRIPT CAPITAL O �� LATIN CAPITAL LETTER O#
			{119979, "P"},  // MA# ( ?? �� P ) MATHEMATICAL SCRIPT CAPITAL P �� LATIN CAPITAL LETTER P#
			{119980, "Q"},  // MA# ( ?? �� Q ) MATHEMATICAL SCRIPT CAPITAL Q �� LATIN CAPITAL LETTER Q#
			{119982, "S"},  // MA# ( ?? �� S ) MATHEMATICAL SCRIPT CAPITAL S �� LATIN CAPITAL LETTER S#
			{119983, "T"},  // MA# ( ?? �� T ) MATHEMATICAL SCRIPT CAPITAL T �� LATIN CAPITAL LETTER T#
			{119984, "U"},  // MA# ( ?? �� U ) MATHEMATICAL SCRIPT CAPITAL U �� LATIN CAPITAL LETTER U#
			{119985, "V"},  // MA# ( ?? �� V ) MATHEMATICAL SCRIPT CAPITAL V �� LATIN CAPITAL LETTER V#
			{119986, "W"},  // MA# ( ?? �� W ) MATHEMATICAL SCRIPT CAPITAL W �� LATIN CAPITAL LETTER W#
			{119987, "X"},  // MA# ( ?? �� X ) MATHEMATICAL SCRIPT CAPITAL X �� LATIN CAPITAL LETTER X#
			{119988, "Y"},  // MA# ( ?? �� Y ) MATHEMATICAL SCRIPT CAPITAL Y �� LATIN CAPITAL LETTER Y#
			{119989, "Z"},  // MA# ( ?? �� Z ) MATHEMATICAL SCRIPT CAPITAL Z �� LATIN CAPITAL LETTER Z#
			{119990, "a"},  // MA# ( ?? �� a ) MATHEMATICAL SCRIPT SMALL A �� LATIN SMALL LETTER A#
			{119991, "b"},  // MA# ( ?? �� b ) MATHEMATICAL SCRIPT SMALL B �� LATIN SMALL LETTER B#
			{119992, "c"},  // MA# ( ?? �� c ) MATHEMATICAL SCRIPT SMALL C �� LATIN SMALL LETTER C#
			{119993, "d"},  // MA# ( ?? �� d ) MATHEMATICAL SCRIPT SMALL D �� LATIN SMALL LETTER D#
			{119995, "f"},  // MA# ( ?? �� f ) MATHEMATICAL SCRIPT SMALL F �� LATIN SMALL LETTER F#
			{119997, "h"},  // MA# ( ?? �� h ) MATHEMATICAL SCRIPT SMALL H �� LATIN SMALL LETTER H#
			{119998, "i"},  // MA# ( ?? �� i ) MATHEMATICAL SCRIPT SMALL I �� LATIN SMALL LETTER I#
			{119999, "j"},  // MA# ( ?? �� j ) MATHEMATICAL SCRIPT SMALL J �� LATIN SMALL LETTER J#
			{120000, "k"},  // MA# ( ?? �� k ) MATHEMATICAL SCRIPT SMALL K �� LATIN SMALL LETTER K#
			{120001, "l"},  // MA# ( ?? �� l ) MATHEMATICAL SCRIPT SMALL L �� LATIN SMALL LETTER L#
			{120002, "rn"}, // MA# ( ?? �� rn ) MATHEMATICAL SCRIPT SMALL M �� LATIN SMALL LETTER R, LATIN SMALL LETTER N# ��m��
			{120003, "n"},  // MA# ( ?? �� n ) MATHEMATICAL SCRIPT SMALL N �� LATIN SMALL LETTER N#
			{120005, "p"},  // MA# ( ?? �� p ) MATHEMATICAL SCRIPT SMALL P �� LATIN SMALL LETTER P#
			{120006, "q"},  // MA# ( ?? �� q ) MATHEMATICAL SCRIPT SMALL Q �� LATIN SMALL LETTER Q#
			{120007, "r"},  // MA# ( ?? �� r ) MATHEMATICAL SCRIPT SMALL R �� LATIN SMALL LETTER R#
			{120008, "s"},  // MA# ( ?? �� s ) MATHEMATICAL SCRIPT SMALL S �� LATIN SMALL LETTER S#
			{120009, "t"},  // MA# ( ?? �� t ) MATHEMATICAL SCRIPT SMALL T �� LATIN SMALL LETTER T#
			{120010, "u"},  // MA# ( ?? �� u ) MATHEMATICAL SCRIPT SMALL U �� LATIN SMALL LETTER U#
			{120011, "v"},  // MA# ( ?? �� v ) MATHEMATICAL SCRIPT SMALL V �� LATIN SMALL LETTER V#
			{120012, "w"},  // MA# ( ?? �� w ) MATHEMATICAL SCRIPT SMALL W �� LATIN SMALL LETTER W#
			{120013, "x"},  // MA# ( ?? �� x ) MATHEMATICAL SCRIPT SMALL X �� LATIN SMALL LETTER X#
			{120014, "y"},  // MA# ( ?? �� y ) MATHEMATICAL SCRIPT SMALL Y �� LATIN SMALL LETTER Y#
			{120015, "z"},  // MA# ( ?? �� z ) MATHEMATICAL SCRIPT SMALL Z �� LATIN SMALL LETTER Z#
			{120016, "A"},  // MA# ( ?? �� A ) MATHEMATICAL BOLD SCRIPT CAPITAL A �� LATIN CAPITAL LETTER A#
			{120017, "B"},  // MA# ( ?? �� B ) MATHEMATICAL BOLD SCRIPT CAPITAL B �� LATIN CAPITAL LETTER B#
			{120018, "C"},  // MA# ( ?? �� C ) MATHEMATICAL BOLD SCRIPT CAPITAL C �� LATIN CAPITAL LETTER C#
			{120019, "D"},  // MA# ( ?? �� D ) MATHEMATICAL BOLD SCRIPT CAPITAL D �� LATIN CAPITAL LETTER D#
			{120020, "E"},  // MA# ( ?? �� E ) MATHEMATICAL BOLD SCRIPT CAPITAL E �� LATIN CAPITAL LETTER E#
			{120021, "F"},  // MA# ( ?? �� F ) MATHEMATICAL BOLD SCRIPT CAPITAL F �� LATIN CAPITAL LETTER F#
			{120022, "G"},  // MA# ( ?? �� G ) MATHEMATICAL BOLD SCRIPT CAPITAL G �� LATIN CAPITAL LETTER G#
			{120023, "H"},  // MA# ( ?? �� H ) MATHEMATICAL BOLD SCRIPT CAPITAL H �� LATIN CAPITAL LETTER H#
			{120024, "l"},  // MA# ( ?? �� l ) MATHEMATICAL BOLD SCRIPT CAPITAL I �� LATIN SMALL LETTER L# ��I��
			{120025, "J"},  // MA# ( ?? �� J ) MATHEMATICAL BOLD SCRIPT CAPITAL J �� LATIN CAPITAL LETTER J#
			{120026, "K"},  // MA# ( ?? �� K ) MATHEMATICAL BOLD SCRIPT CAPITAL K �� LATIN CAPITAL LETTER K#
			{120027, "L"},  // MA# ( ?? �� L ) MATHEMATICAL BOLD SCRIPT CAPITAL L �� LATIN CAPITAL LETTER L#
			{120028, "M"},  // MA# ( ?? �� M ) MATHEMATICAL BOLD SCRIPT CAPITAL M �� LATIN CAPITAL LETTER M#
			{120029, "N"},  // MA# ( ?? �� N ) MATHEMATICAL BOLD SCRIPT CAPITAL N �� LATIN CAPITAL LETTER N#
			{120030, "O"},  // MA# ( ?? �� O ) MATHEMATICAL BOLD SCRIPT CAPITAL O �� LATIN CAPITAL LETTER O#
			{120031, "P"},  // MA# ( ?? �� P ) MATHEMATICAL BOLD SCRIPT CAPITAL P �� LATIN CAPITAL LETTER P#
			{120032, "Q"},  // MA# ( ?? �� Q ) MATHEMATICAL BOLD SCRIPT CAPITAL Q �� LATIN CAPITAL LETTER Q#
			{120033, "R"},  // MA# ( ?? �� R ) MATHEMATICAL BOLD SCRIPT CAPITAL R �� LATIN CAPITAL LETTER R#
			{120034, "S"},  // MA# ( ?? �� S ) MATHEMATICAL BOLD SCRIPT CAPITAL S �� LATIN CAPITAL LETTER S#
			{120035, "T"},  // MA# ( ?? �� T ) MATHEMATICAL BOLD SCRIPT CAPITAL T �� LATIN CAPITAL LETTER T#
			{120036, "U"},  // MA# ( ?? �� U ) MATHEMATICAL BOLD SCRIPT CAPITAL U �� LATIN CAPITAL LETTER U#
			{120037, "V"},  // MA# ( ?? �� V ) MATHEMATICAL BOLD SCRIPT CAPITAL V �� LATIN CAPITAL LETTER V#
			{120038, "W"},  // MA# ( ?? �� W ) MATHEMATICAL BOLD SCRIPT CAPITAL W �� LATIN CAPITAL LETTER W#
			{120039, "X"},  // MA# ( ?? �� X ) MATHEMATICAL BOLD SCRIPT CAPITAL X �� LATIN CAPITAL LETTER X#
			{120040, "Y"},  // MA# ( ?? �� Y ) MATHEMATICAL BOLD SCRIPT CAPITAL Y �� LATIN CAPITAL LETTER Y#
			{120041, "Z"},  // MA# ( ?? �� Z ) MATHEMATICAL BOLD SCRIPT CAPITAL Z �� LATIN CAPITAL LETTER Z#
			{120042, "a"},  // MA# ( ?? �� a ) MATHEMATICAL BOLD SCRIPT SMALL A �� LATIN SMALL LETTER A#
			{120043, "b"},  // MA# ( ?? �� b ) MATHEMATICAL BOLD SCRIPT SMALL B �� LATIN SMALL LETTER B#
			{120044, "c"},  // MA# ( ?? �� c ) MATHEMATICAL BOLD SCRIPT SMALL C �� LATIN SMALL LETTER C#
			{120045, "d"},  // MA# ( ?? �� d ) MATHEMATICAL BOLD SCRIPT SMALL D �� LATIN SMALL LETTER D#
			{120046, "e"},  // MA# ( ?? �� e ) MATHEMATICAL BOLD SCRIPT SMALL E �� LATIN SMALL LETTER E#
			{120047, "f"},  // MA# ( ?? �� f ) MATHEMATICAL BOLD SCRIPT SMALL F �� LATIN SMALL LETTER F#
			{120048, "g"},  // MA# ( ?? �� g ) MATHEMATICAL BOLD SCRIPT SMALL G �� LATIN SMALL LETTER G#
			{120049, "h"},  // MA# ( ?? �� h ) MATHEMATICAL BOLD SCRIPT SMALL H �� LATIN SMALL LETTER H#
			{120050, "i"},  // MA# ( ?? �� i ) MATHEMATICAL BOLD SCRIPT SMALL I �� LATIN SMALL LETTER I#
			{120051, "j"},  // MA# ( ?? �� j ) MATHEMATICAL BOLD SCRIPT SMALL J �� LATIN SMALL LETTER J#
			{120052, "k"},  // MA# ( ?? �� k ) MATHEMATICAL BOLD SCRIPT SMALL K �� LATIN SMALL LETTER K#
			{120053, "l"},  // MA# ( ?? �� l ) MATHEMATICAL BOLD SCRIPT SMALL L �� LATIN SMALL LETTER L#
			{120054, "rn"}, // MA# ( ?? �� rn ) MATHEMATICAL BOLD SCRIPT SMALL M �� LATIN SMALL LETTER R, LATIN SMALL LETTER N# ��m��
			{120055, "n"},  // MA# ( ?? �� n ) MATHEMATICAL BOLD SCRIPT SMALL N �� LATIN SMALL LETTER N#
			{120056, "o"},  // MA# ( ?? �� o ) MATHEMATICAL BOLD SCRIPT SMALL O �� LATIN SMALL LETTER O#
			{120057, "p"},  // MA# ( ?? �� p ) MATHEMATICAL BOLD SCRIPT SMALL P �� LATIN SMALL LETTER P#
			{120058, "q"},  // MA# ( ?? �� q ) MATHEMATICAL BOLD SCRIPT SMALL Q �� LATIN SMALL LETTER Q#
			{120059, "r"},  // MA# ( ?? �� r ) MATHEMATICAL BOLD SCRIPT SMALL R �� LATIN SMALL LETTER R#
			{120060, "s"},  // MA# ( ?? �� s ) MATHEMATICAL BOLD SCRIPT SMALL S �� LATIN SMALL LETTER S#
			{120061, "t"},  // MA# ( ?? �� t ) MATHEMATICAL BOLD SCRIPT SMALL T �� LATIN SMALL LETTER T#
			{120062, "u"},  // MA# ( ?? �� u ) MATHEMATICAL BOLD SCRIPT SMALL U �� LATIN SMALL LETTER U#
			{120063, "v"},  // MA# ( ?? �� v ) MATHEMATICAL BOLD SCRIPT SMALL V �� LATIN SMALL LETTER V#
			{120064, "w"},  // MA# ( ?? �� w ) MATHEMATICAL BOLD SCRIPT SMALL W �� LATIN SMALL LETTER W#
			{120065, "x"},  // MA# ( ?? �� x ) MATHEMATICAL BOLD SCRIPT SMALL X �� LATIN SMALL LETTER X#
			{120066, "y"},  // MA# ( ?? �� y ) MATHEMATICAL BOLD SCRIPT SMALL Y �� LATIN SMALL LETTER Y#
			{120067, "z"},  // MA# ( ?? �� z ) MATHEMATICAL BOLD SCRIPT SMALL Z �� LATIN SMALL LETTER Z#
			{120068, "A"},  // MA# ( ?? �� A ) MATHEMATICAL FRAKTUR CAPITAL A �� LATIN CAPITAL LETTER A#
			{120069, "B"},  // MA# ( ?? �� B ) MATHEMATICAL FRAKTUR CAPITAL B �� LATIN CAPITAL LETTER B#
			{120071, "D"},  // MA# ( ?? �� D ) MATHEMATICAL FRAKTUR CAPITAL D �� LATIN CAPITAL LETTER D#
			{120072, "E"},  // MA# ( ?? �� E ) MATHEMATICAL FRAKTUR CAPITAL E �� LATIN CAPITAL LETTER E#
			{120073, "F"},  // MA# ( ?? �� F ) MATHEMATICAL FRAKTUR CAPITAL F �� LATIN CAPITAL LETTER F#
			{120074, "G"},  // MA# ( ?? �� G ) MATHEMATICAL FRAKTUR CAPITAL G �� LATIN CAPITAL LETTER G#
			{120077, "J"},  // MA# ( ?? �� J ) MATHEMATICAL FRAKTUR CAPITAL J �� LATIN CAPITAL LETTER J#
			{120078, "K"},  // MA# ( ?? �� K ) MATHEMATICAL FRAKTUR CAPITAL K �� LATIN CAPITAL LETTER K#
			{120079, "L"},  // MA# ( ?? �� L ) MATHEMATICAL FRAKTUR CAPITAL L �� LATIN CAPITAL LETTER L#
			{120080, "M"},  // MA# ( ?? �� M ) MATHEMATICAL FRAKTUR CAPITAL M �� LATIN CAPITAL LETTER M#
			{120081, "N"},  // MA# ( ?? �� N ) MATHEMATICAL FRAKTUR CAPITAL N �� LATIN CAPITAL LETTER N#
			{120082, "O"},  // MA# ( ?? �� O ) MATHEMATICAL FRAKTUR CAPITAL O �� LATIN CAPITAL LETTER O#
			{120083, "P"},  // MA# ( ?? �� P ) MATHEMATICAL FRAKTUR CAPITAL P �� LATIN CAPITAL LETTER P#
			{120084, "Q"},  // MA# ( ?? �� Q ) MATHEMATICAL FRAKTUR CAPITAL Q �� LATIN CAPITAL LETTER Q#
			{120086, "S"},  // MA# ( ?? �� S ) MATHEMATICAL FRAKTUR CAPITAL S �� LATIN CAPITAL LETTER S#
			{120087, "T"},  // MA# ( ?? �� T ) MATHEMATICAL FRAKTUR CAPITAL T �� LATIN CAPITAL LETTER T#
			{120088, "U"},  // MA# ( ?? �� U ) MATHEMATICAL FRAKTUR CAPITAL U �� LATIN CAPITAL LETTER U#
			{120089, "V"},  // MA# ( ?? �� V ) MATHEMATICAL FRAKTUR CAPITAL V �� LATIN CAPITAL LETTER V#
			{120090, "W"},  // MA# ( ?? �� W ) MATHEMATICAL FRAKTUR CAPITAL W �� LATIN CAPITAL LETTER W#
			{120091, "X"},  // MA# ( ?? �� X ) MATHEMATICAL FRAKTUR CAPITAL X �� LATIN CAPITAL LETTER X#
			{120092, "Y"},  // MA# ( ?? �� Y ) MATHEMATICAL FRAKTUR CAPITAL Y �� LATIN CAPITAL LETTER Y#
			{120094, "a"},  // MA# ( ?? �� a ) MATHEMATICAL FRAKTUR SMALL A �� LATIN SMALL LETTER A#
			{120095, "b"},  // MA# ( ?? �� b ) MATHEMATICAL FRAKTUR SMALL B �� LATIN SMALL LETTER B#
			{120096, "c"},  // MA# ( ?? �� c ) MATHEMATICAL FRAKTUR SMALL C �� LATIN SMALL LETTER C#
			{120097, "d"},  // MA# ( ?? �� d ) MATHEMATICAL FRAKTUR SMALL D �� LATIN SMALL LETTER D#
			{120098, "e"},  // MA# ( ?? �� e ) MATHEMATICAL FRAKTUR SMALL E �� LATIN SMALL LETTER E#
			{120099, "f"},  // MA# ( ?? �� f ) MATHEMATICAL FRAKTUR SMALL F �� LATIN SMALL LETTER F#
			{120100, "g"},  // MA# ( ?? �� g ) MATHEMATICAL FRAKTUR SMALL G �� LATIN SMALL LETTER G#
			{120101, "h"},  // MA# ( ?? �� h ) MATHEMATICAL FRAKTUR SMALL H �� LATIN SMALL LETTER H#
			{120102, "i"},  // MA# ( ?? �� i ) MATHEMATICAL FRAKTUR SMALL I �� LATIN SMALL LETTER I#
			{120103, "j"},  // MA# ( ?? �� j ) MATHEMATICAL FRAKTUR SMALL J �� LATIN SMALL LETTER J#
			{120104, "k"},  // MA# ( ?? �� k ) MATHEMATICAL FRAKTUR SMALL K �� LATIN SMALL LETTER K#
			{120105, "l"},  // MA# ( ?? �� l ) MATHEMATICAL FRAKTUR SMALL L �� LATIN SMALL LETTER L#
			{120106, "rn"}, // MA# ( ?? �� rn ) MATHEMATICAL FRAKTUR SMALL M �� LATIN SMALL LETTER R, LATIN SMALL LETTER N# ��m��
			{120107, "n"},  // MA# ( ?? �� n ) MATHEMATICAL FRAKTUR SMALL N �� LATIN SMALL LETTER N#
			{120108, "o"},  // MA# ( ?? �� o ) MATHEMATICAL FRAKTUR SMALL O �� LATIN SMALL LETTER O#
			{120109, "p"},  // MA# ( ?? �� p ) MATHEMATICAL FRAKTUR SMALL P �� LATIN SMALL LETTER P#
			{120110, "q"},  // MA# ( ?? �� q ) MATHEMATICAL FRAKTUR SMALL Q �� LATIN SMALL LETTER Q#
			{120111, "r"},  // MA# ( ?? �� r ) MATHEMATICAL FRAKTUR SMALL R �� LATIN SMALL LETTER R#
			{120112, "s"},  // MA# ( ?? �� s ) MATHEMATICAL FRAKTUR SMALL S �� LATIN SMALL LETTER S#
			{120113, "t"},  // MA# ( ?? �� t ) MATHEMATICAL FRAKTUR SMALL T �� LATIN SMALL LETTER T#
			{120114, "u"},  // MA# ( ?? �� u ) MATHEMATICAL FRAKTUR SMALL U �� LATIN SMALL LETTER U#
			{120115, "v"},  // MA# ( ?? �� v ) MATHEMATICAL FRAKTUR SMALL V �� LATIN SMALL LETTER V#
			{120116, "w"},  // MA# ( ?? �� w ) MATHEMATICAL FRAKTUR SMALL W �� LATIN SMALL LETTER W#
			{120117, "x"},  // MA# ( ?? �� x ) MATHEMATICAL FRAKTUR SMALL X �� LATIN SMALL LETTER X#
			{120118, "y"},  // MA# ( ?? �� y ) MATHEMATICAL FRAKTUR SMALL Y �� LATIN SMALL LETTER Y#
			{120119, "z"},  // MA# ( ?? �� z ) MATHEMATICAL FRAKTUR SMALL Z �� LATIN SMALL LETTER Z#
			{120120, "A"},  // MA# ( ?? �� A ) MATHEMATICAL DOUBLE-STRUCK CAPITAL A �� LATIN CAPITAL LETTER A#
			{120121, "B"},  // MA# ( ?? �� B ) MATHEMATICAL DOUBLE-STRUCK CAPITAL B �� LATIN CAPITAL LETTER B#
			{120123, "D"},  // MA# ( ?? �� D ) MATHEMATICAL DOUBLE-STRUCK CAPITAL D �� LATIN CAPITAL LETTER D#
			{120124, "E"},  // MA# ( ?? �� E ) MATHEMATICAL DOUBLE-STRUCK CAPITAL E �� LATIN CAPITAL LETTER E#
			{120125, "F"},  // MA# ( ?? �� F ) MATHEMATICAL DOUBLE-STRUCK CAPITAL F �� LATIN CAPITAL LETTER F#
			{120126, "G"},  // MA# ( ?? �� G ) MATHEMATICAL DOUBLE-STRUCK CAPITAL G �� LATIN CAPITAL LETTER G#
			{120128, "l"},  // MA# ( ?? �� l ) MATHEMATICAL DOUBLE-STRUCK CAPITAL I �� LATIN SMALL LETTER L# ��I��
			{120129, "J"},  // MA# ( ?? �� J ) MATHEMATICAL DOUBLE-STRUCK CAPITAL J �� LATIN CAPITAL LETTER J#
			{120130, "K"},  // MA# ( ?? �� K ) MATHEMATICAL DOUBLE-STRUCK CAPITAL K �� LATIN CAPITAL LETTER K#
			{120131, "L"},  // MA# ( ?? �� L ) MATHEMATICAL DOUBLE-STRUCK CAPITAL L �� LATIN CAPITAL LETTER L#
			{120132, "M"},  // MA# ( ?? �� M ) MATHEMATICAL DOUBLE-STRUCK CAPITAL M �� LATIN CAPITAL LETTER M#
			{120134, "O"},  // MA# ( ?? �� O ) MATHEMATICAL DOUBLE-STRUCK CAPITAL O �� LATIN CAPITAL LETTER O#
			{120138, "S"},  // MA# ( ?? �� S ) MATHEMATICAL DOUBLE-STRUCK CAPITAL S �� LATIN CAPITAL LETTER S#
			{120139, "T"},  // MA# ( ?? �� T ) MATHEMATICAL DOUBLE-STRUCK CAPITAL T �� LATIN CAPITAL LETTER T#
			{120140, "U"},  // MA# ( ?? �� U ) MATHEMATICAL DOUBLE-STRUCK CAPITAL U �� LATIN CAPITAL LETTER U#
			{120141, "V"},  // MA# ( ?? �� V ) MATHEMATICAL DOUBLE-STRUCK CAPITAL V �� LATIN CAPITAL LETTER V#
			{120142, "W"},  // MA# ( ?? �� W ) MATHEMATICAL DOUBLE-STRUCK CAPITAL W �� LATIN CAPITAL LETTER W#
			{120143, "X"},  // MA# ( ?? �� X ) MATHEMATICAL DOUBLE-STRUCK CAPITAL X �� LATIN CAPITAL LETTER X#
			{120144, "Y"},  // MA# ( ?? �� Y ) MATHEMATICAL DOUBLE-STRUCK CAPITAL Y �� LATIN CAPITAL LETTER Y#
			{120146, "a"},  // MA# ( ?? �� a ) MATHEMATICAL DOUBLE-STRUCK SMALL A �� LATIN SMALL LETTER A#
			{120147, "b"},  // MA# ( ?? �� b ) MATHEMATICAL DOUBLE-STRUCK SMALL B �� LATIN SMALL LETTER B#
			{120148, "c"},  // MA# ( ?? �� c ) MATHEMATICAL DOUBLE-STRUCK SMALL C �� LATIN SMALL LETTER C#
			{120149, "d"},  // MA# ( ?? �� d ) MATHEMATICAL DOUBLE-STRUCK SMALL D �� LATIN SMALL LETTER D#
			{120150, "e"},  // MA# ( ?? �� e ) MATHEMATICAL DOUBLE-STRUCK SMALL E �� LATIN SMALL LETTER E#
			{120151, "f"},  // MA# ( ?? �� f ) MATHEMATICAL DOUBLE-STRUCK SMALL F �� LATIN SMALL LETTER F#
			{120152, "g"},  // MA# ( ?? �� g ) MATHEMATICAL DOUBLE-STRUCK SMALL G �� LATIN SMALL LETTER G#
			{120153, "h"},  // MA# ( ?? �� h ) MATHEMATICAL DOUBLE-STRUCK SMALL H �� LATIN SMALL LETTER H#
			{120154, "i"},  // MA# ( ?? �� i ) MATHEMATICAL DOUBLE-STRUCK SMALL I �� LATIN SMALL LETTER I#
			{120155, "j"},  // MA# ( ?? �� j ) MATHEMATICAL DOUBLE-STRUCK SMALL J �� LATIN SMALL LETTER J#
			{120156, "k"},  // MA# ( ?? �� k ) MATHEMATICAL DOUBLE-STRUCK SMALL K �� LATIN SMALL LETTER K#
			{120157, "l"},  // MA# ( ?? �� l ) MATHEMATICAL DOUBLE-STRUCK SMALL L �� LATIN SMALL LETTER L#
			{120158, "rn"}, // MA# ( ?? �� rn ) MATHEMATICAL DOUBLE-STRUCK SMALL M �� LATIN SMALL LETTER R, LATIN SMALL LETTER N# ��m��
			{120159, "n"},  // MA# ( ?? �� n ) MATHEMATICAL DOUBLE-STRUCK SMALL N �� LATIN SMALL LETTER N#
			{120160, "o"},  // MA# ( ?? �� o ) MATHEMATICAL DOUBLE-STRUCK SMALL O �� LATIN SMALL LETTER O#
			{120161, "p"},  // MA# ( ?? �� p ) MATHEMATICAL DOUBLE-STRUCK SMALL P �� LATIN SMALL LETTER P#
			{120162, "q"},  // MA# ( ?? �� q ) MATHEMATICAL DOUBLE-STRUCK SMALL Q �� LATIN SMALL LETTER Q#
			{120163, "r"},  // MA# ( ?? �� r ) MATHEMATICAL DOUBLE-STRUCK SMALL R �� LATIN SMALL LETTER R#
			{120164, "s"},  // MA# ( ?? �� s ) MATHEMATICAL DOUBLE-STRUCK SMALL S �� LATIN SMALL LETTER S#
			{120165, "t"},  // MA# ( ?? �� t ) MATHEMATICAL DOUBLE-STRUCK SMALL T �� LATIN SMALL LETTER T#
			{120166, "u"},  // MA# ( ?? �� u ) MATHEMATICAL DOUBLE-STRUCK SMALL U �� LATIN SMALL LETTER U#
			{120167, "v"},  // MA# ( ?? �� v ) MATHEMATICAL DOUBLE-STRUCK SMALL V �� LATIN SMALL LETTER V#
			{120168, "w"},  // MA# ( ?? �� w ) MATHEMATICAL DOUBLE-STRUCK SMALL W �� LATIN SMALL LETTER W#
			{120169, "x"},  // MA# ( ?? �� x ) MATHEMATICAL DOUBLE-STRUCK SMALL X �� LATIN SMALL LETTER X#
			{120170, "y"},  // MA# ( ?? �� y ) MATHEMATICAL DOUBLE-STRUCK SMALL Y �� LATIN SMALL LETTER Y#
			{120171, "z"},  // MA# ( ?? �� z ) MATHEMATICAL DOUBLE-STRUCK SMALL Z �� LATIN SMALL LETTER Z#
			{120172, "A"},  // MA# ( ?? �� A ) MATHEMATICAL BOLD FRAKTUR CAPITAL A �� LATIN CAPITAL LETTER A#
			{120173, "B"},  // MA# ( ?? �� B ) MATHEMATICAL BOLD FRAKTUR CAPITAL B �� LATIN CAPITAL LETTER B#
			{120174, "C"},  // MA# ( ?? �� C ) MATHEMATICAL BOLD FRAKTUR CAPITAL C �� LATIN CAPITAL LETTER C#
			{120175, "D"},  // MA# ( ?? �� D ) MATHEMATICAL BOLD FRAKTUR CAPITAL D �� LATIN CAPITAL LETTER D#
			{120176, "E"},  // MA# ( ?? �� E ) MATHEMATICAL BOLD FRAKTUR CAPITAL E �� LATIN CAPITAL LETTER E#
			{120177, "F"},  // MA# ( ?? �� F ) MATHEMATICAL BOLD FRAKTUR CAPITAL F �� LATIN CAPITAL LETTER F#
			{120178, "G"},  // MA# ( ?? �� G ) MATHEMATICAL BOLD FRAKTUR CAPITAL G �� LATIN CAPITAL LETTER G#
			{120179, "H"},  // MA# ( ?? �� H ) MATHEMATICAL BOLD FRAKTUR CAPITAL H �� LATIN CAPITAL LETTER H#
			{120180, "l"},  // MA# ( ?? �� l ) MATHEMATICAL BOLD FRAKTUR CAPITAL I �� LATIN SMALL LETTER L# ��I��
			{120181, "J"},  // MA# ( ?? �� J ) MATHEMATICAL BOLD FRAKTUR CAPITAL J �� LATIN CAPITAL LETTER J#
			{120182, "K"},  // MA# ( ?? �� K ) MATHEMATICAL BOLD FRAKTUR CAPITAL K �� LATIN CAPITAL LETTER K#
			{120183, "L"},  // MA# ( ?? �� L ) MATHEMATICAL BOLD FRAKTUR CAPITAL L �� LATIN CAPITAL LETTER L#
			{120184, "M"},  // MA# ( ?? �� M ) MATHEMATICAL BOLD FRAKTUR CAPITAL M �� LATIN CAPITAL LETTER M#
			{120185, "N"},  // MA# ( ?? �� N ) MATHEMATICAL BOLD FRAKTUR CAPITAL N �� LATIN CAPITAL LETTER N#
			{120186, "O"},  // MA# ( ?? �� O ) MATHEMATICAL BOLD FRAKTUR CAPITAL O �� LATIN CAPITAL LETTER O#
			{120187, "P"},  // MA# ( ?? �� P ) MATHEMATICAL BOLD FRAKTUR CAPITAL P �� LATIN CAPITAL LETTER P#
			{120188, "Q"},  // MA# ( ?? �� Q ) MATHEMATICAL BOLD FRAKTUR CAPITAL Q �� LATIN CAPITAL LETTER Q#
			{120189, "R"},  // MA# ( ?? �� R ) MATHEMATICAL BOLD FRAKTUR CAPITAL R �� LATIN CAPITAL LETTER R#
			{120190, "S"},  // MA# ( ?? �� S ) MATHEMATICAL BOLD FRAKTUR CAPITAL S �� LATIN CAPITAL LETTER S#
			{120191, "T"},  // MA# ( ?? �� T ) MATHEMATICAL BOLD FRAKTUR CAPITAL T �� LATIN CAPITAL LETTER T#
			{120192, "U"},  // MA# ( ?? �� U ) MATHEMATICAL BOLD FRAKTUR CAPITAL U �� LATIN CAPITAL LETTER U#
			{120193, "V"},  // MA# ( ?? �� V ) MATHEMATICAL BOLD FRAKTUR CAPITAL V �� LATIN CAPITAL LETTER V#
			{120194, "W"},  // MA# ( ?? �� W ) MATHEMATICAL BOLD FRAKTUR CAPITAL W �� LATIN CAPITAL LETTER W#
			{120195, "X"},  // MA# ( ?? �� X ) MATHEMATICAL BOLD FRAKTUR CAPITAL X �� LATIN CAPITAL LETTER X#
			{120196, "Y"},  // MA# ( ?? �� Y ) MATHEMATICAL BOLD FRAKTUR CAPITAL Y �� LATIN CAPITAL LETTER Y#
			{120197, "Z"},  // MA# ( ?? �� Z ) MATHEMATICAL BOLD FRAKTUR CAPITAL Z �� LATIN CAPITAL LETTER Z#
			{120198, "a"},  // MA# ( ?? �� a ) MATHEMATICAL BOLD FRAKTUR SMALL A �� LATIN SMALL LETTER A#
			{120199, "b"},  // MA# ( ?? �� b ) MATHEMATICAL BOLD FRAKTUR SMALL B �� LATIN SMALL LETTER B#
			{120200, "c"},  // MA# ( ?? �� c ) MATHEMATICAL BOLD FRAKTUR SMALL C �� LATIN SMALL LETTER C#
			{120201, "d"},  // MA# ( ?? �� d ) MATHEMATICAL BOLD FRAKTUR SMALL D �� LATIN SMALL LETTER D#
			{120202, "e"},  // MA# ( ?? �� e ) MATHEMATICAL BOLD FRAKTUR SMALL E �� LATIN SMALL LETTER E#
			{120203, "f"},  // MA# ( ?? �� f ) MATHEMATICAL BOLD FRAKTUR SMALL F �� LATIN SMALL LETTER F#
			{120204, "g"},  // MA# ( ?? �� g ) MATHEMATICAL BOLD FRAKTUR SMALL G �� LATIN SMALL LETTER G#
			{120205, "h"},  // MA# ( ?? �� h ) MATHEMATICAL BOLD FRAKTUR SMALL H �� LATIN SMALL LETTER H#
			{120206, "i"},  // MA# ( ?? �� i ) MATHEMATICAL BOLD FRAKTUR SMALL I �� LATIN SMALL LETTER I#
			{120207, "j"},  // MA# ( ?? �� j ) MATHEMATICAL BOLD FRAKTUR SMALL J �� LATIN SMALL LETTER J#
			{120208, "k"},  // MA# ( ?? �� k ) MATHEMATICAL BOLD FRAKTUR SMALL K �� LATIN SMALL LETTER K#
			{120209, "l"},  // MA# ( ?? �� l ) MATHEMATICAL BOLD FRAKTUR SMALL L �� LATIN SMALL LETTER L#
			{120210, "rn"}, // MA# ( ?? �� rn ) MATHEMATICAL BOLD FRAKTUR SMALL M �� LATIN SMALL LETTER R, LATIN SMALL LETTER N# ��m��
			{120211, "n"},  // MA# ( ?? �� n ) MATHEMATICAL BOLD FRAKTUR SMALL N �� LATIN SMALL LETTER N#
			{120212, "o"},  // MA# ( ?? �� o ) MATHEMATICAL BOLD FRAKTUR SMALL O �� LATIN SMALL LETTER O#
			{120213, "p"},  // MA# ( ?? �� p ) MATHEMATICAL BOLD FRAKTUR SMALL P �� LATIN SMALL LETTER P#
			{120214, "q"},  // MA# ( ?? �� q ) MATHEMATICAL BOLD FRAKTUR SMALL Q �� LATIN SMALL LETTER Q#
			{120215, "r"},  // MA# ( ?? �� r ) MATHEMATICAL BOLD FRAKTUR SMALL R �� LATIN SMALL LETTER R#
			{120216, "s"},  // MA# ( ?? �� s ) MATHEMATICAL BOLD FRAKTUR SMALL S �� LATIN SMALL LETTER S#
			{120217, "t"},  // MA# ( ?? �� t ) MATHEMATICAL BOLD FRAKTUR SMALL T �� LATIN SMALL LETTER T#
			{120218, "u"},  // MA# ( ?? �� u ) MATHEMATICAL BOLD FRAKTUR SMALL U �� LATIN SMALL LETTER U#
			{120219, "v"},  // MA# ( ?? �� v ) MATHEMATICAL BOLD FRAKTUR SMALL V �� LATIN SMALL LETTER V#
			{120220, "w"},  // MA# ( ?? �� w ) MATHEMATICAL BOLD FRAKTUR SMALL W �� LATIN SMALL LETTER W#
			{120221, "x"},  // MA# ( ?? �� x ) MATHEMATICAL BOLD FRAKTUR SMALL X �� LATIN SMALL LETTER X#
			{120222, "y"},  // MA# ( ?? �� y ) MATHEMATICAL BOLD FRAKTUR SMALL Y �� LATIN SMALL LETTER Y#
			{120223, "z"},  // MA# ( ?? �� z ) MATHEMATICAL BOLD FRAKTUR SMALL Z �� LATIN SMALL LETTER Z#
			{120224, "A"},  // MA# ( ?? �� A ) MATHEMATICAL SANS-SERIF CAPITAL A �� LATIN CAPITAL LETTER A#
			{120225, "B"},  // MA# ( ?? �� B ) MATHEMATICAL SANS-SERIF CAPITAL B �� LATIN CAPITAL LETTER B#
			{120226, "C"},  // MA# ( ?? �� C ) MATHEMATICAL SANS-SERIF CAPITAL C �� LATIN CAPITAL LETTER C#
			{120227, "D"},  // MA# ( ?? �� D ) MATHEMATICAL SANS-SERIF CAPITAL D �� LATIN CAPITAL LETTER D#
			{120228, "E"},  // MA# ( ?? �� E ) MATHEMATICAL SANS-SERIF CAPITAL E �� LATIN CAPITAL LETTER E#
			{120229, "F"},  // MA# ( ?? �� F ) MATHEMATICAL SANS-SERIF CAPITAL F �� LATIN CAPITAL LETTER F#
			{120230, "G"},  // MA# ( ?? �� G ) MATHEMATICAL SANS-SERIF CAPITAL G �� LATIN CAPITAL LETTER G#
			{120231, "H"},  // MA# ( ?? �� H ) MATHEMATICAL SANS-SERIF CAPITAL H �� LATIN CAPITAL LETTER H#
			{120232, "l"},  // MA# ( ?? �� l ) MATHEMATICAL SANS-SERIF CAPITAL I �� LATIN SMALL LETTER L# ��I��
			{120233, "J"},  // MA# ( ?? �� J ) MATHEMATICAL SANS-SERIF CAPITAL J �� LATIN CAPITAL LETTER J#
			{120234, "K"},  // MA# ( ?? �� K ) MATHEMATICAL SANS-SERIF CAPITAL K �� LATIN CAPITAL LETTER K#
			{120235, "L"},  // MA# ( ?? �� L ) MATHEMATICAL SANS-SERIF CAPITAL L �� LATIN CAPITAL LETTER L#
			{120236, "M"},  // MA# ( ?? �� M ) MATHEMATICAL SANS-SERIF CAPITAL M �� LATIN CAPITAL LETTER M#
			{120237, "N"},  // MA# ( ?? �� N ) MATHEMATICAL SANS-SERIF CAPITAL N �� LATIN CAPITAL LETTER N#
			{120238, "O"},  // MA# ( ?? �� O ) MATHEMATICAL SANS-SERIF CAPITAL O �� LATIN CAPITAL LETTER O#
			{120239, "P"},  // MA# ( ?? �� P ) MATHEMATICAL SANS-SERIF CAPITAL P �� LATIN CAPITAL LETTER P#
			{120240, "Q"},  // MA# ( ?? �� Q ) MATHEMATICAL SANS-SERIF CAPITAL Q �� LATIN CAPITAL LETTER Q#
			{120241, "R"},  // MA# ( ?? �� R ) MATHEMATICAL SANS-SERIF CAPITAL R �� LATIN CAPITAL LETTER R#
			{120242, "S"},  // MA# ( ?? �� S ) MATHEMATICAL SANS-SERIF CAPITAL S �� LATIN CAPITAL LETTER S#
			{120243, "T"},  // MA# ( ?? �� T ) MATHEMATICAL SANS-SERIF CAPITAL T �� LATIN CAPITAL LETTER T#
			{120244, "U"},  // MA# ( ?? �� U ) MATHEMATICAL SANS-SERIF CAPITAL U �� LATIN CAPITAL LETTER U#
			{120245, "V"},  // MA# ( ?? �� V ) MATHEMATICAL SANS-SERIF CAPITAL V �� LATIN CAPITAL LETTER V#
			{120246, "W"},  // MA# ( ?? �� W ) MATHEMATICAL SANS-SERIF CAPITAL W �� LATIN CAPITAL LETTER W#
			{120247, "X"},  // MA# ( ?? �� X ) MATHEMATICAL SANS-SERIF CAPITAL X �� LATIN CAPITAL LETTER X#
			{120248, "Y"},  // MA# ( ?? �� Y ) MATHEMATICAL SANS-SERIF CAPITAL Y �� LATIN CAPITAL LETTER Y#
			{120249, "Z"},  // MA# ( ?? �� Z ) MATHEMATICAL SANS-SERIF CAPITAL Z �� LATIN CAPITAL LETTER Z#
			{120250, "a"},  // MA# ( ?? �� a ) MATHEMATICAL SANS-SERIF SMALL A �� LATIN SMALL LETTER A#
			{120251, "b"},  // MA# ( ?? �� b ) MATHEMATICAL SANS-SERIF SMALL B �� LATIN SMALL LETTER B#
			{120252, "c"},  // MA# ( ?? �� c ) MATHEMATICAL SANS-SERIF SMALL C �� LATIN SMALL LETTER C#
			{120253, "d"},  // MA# ( ?? �� d ) MATHEMATICAL SANS-SERIF SMALL D �� LATIN SMALL LETTER D#
			{120254, "e"},  // MA# ( ?? �� e ) MATHEMATICAL SANS-SERIF SMALL E �� LATIN SMALL LETTER E#
			{120255, "f"},  // MA# ( ?? �� f ) MATHEMATICAL SANS-SERIF SMALL F �� LATIN SMALL LETTER F#
			{120256, "g"},  // MA# ( ?? �� g ) MATHEMATICAL SANS-SERIF SMALL G �� LATIN SMALL LETTER G#
			{120257, "h"},  // MA# ( ?? �� h ) MATHEMATICAL SANS-SERIF SMALL H �� LATIN SMALL LETTER H#
			{120258, "i"},  // MA# ( ?? �� i ) MATHEMATICAL SANS-SERIF SMALL I �� LATIN SMALL LETTER I#
			{120259, "j"},  // MA# ( ?? �� j ) MATHEMATICAL SANS-SERIF SMALL J �� LATIN SMALL LETTER J#
			{120260, "k"},  // MA# ( ?? �� k ) MATHEMATICAL SANS-SERIF SMALL K �� LATIN SMALL LETTER K#
			{120261, "l"},  // MA# ( ?? �� l ) MATHEMATICAL SANS-SERIF SMALL L �� LATIN SMALL LETTER L#
			{120262, "rn"}, // MA# ( ?? �� rn ) MATHEMATICAL SANS-SERIF SMALL M �� LATIN SMALL LETTER R, LATIN SMALL LETTER N# ��m��
			{120263, "n"},  // MA# ( ?? �� n ) MATHEMATICAL SANS-SERIF SMALL N �� LATIN SMALL LETTER N#
			{120264, "o"},  // MA# ( ?? �� o ) MATHEMATICAL SANS-SERIF SMALL O �� LATIN SMALL LETTER O#
			{120265, "p"},  // MA# ( ?? �� p ) MATHEMATICAL SANS-SERIF SMALL P �� LATIN SMALL LETTER P#
			{120266, "q"},  // MA# ( ?? �� q ) MATHEMATICAL SANS-SERIF SMALL Q �� LATIN SMALL LETTER Q#
			{120267, "r"},  // MA# ( ?? �� r ) MATHEMATICAL SANS-SERIF SMALL R �� LATIN SMALL LETTER R#
			{120268, "s"},  // MA# ( ?? �� s ) MATHEMATICAL SANS-SERIF SMALL S �� LATIN SMALL LETTER S#
			{120269, "t"},  // MA# ( ?? �� t ) MATHEMATICAL SANS-SERIF SMALL T �� LATIN SMALL LETTER T#
			{120270, "u"},  // MA# ( ?? �� u ) MATHEMATICAL SANS-SERIF SMALL U �� LATIN SMALL LETTER U#
			{120271, "v"},  // MA# ( ?? �� v ) MATHEMATICAL SANS-SERIF SMALL V �� LATIN SMALL LETTER V#
			{120272, "w"},  // MA# ( ?? �� w ) MATHEMATICAL SANS-SERIF SMALL W �� LATIN SMALL LETTER W#
			{120273, "x"},  // MA# ( ?? �� x ) MATHEMATICAL SANS-SERIF SMALL X �� LATIN SMALL LETTER X#
			{120274, "y"},  // MA# ( ?? �� y ) MATHEMATICAL SANS-SERIF SMALL Y �� LATIN SMALL LETTER Y#
			{120275, "z"},  // MA# ( ?? �� z ) MATHEMATICAL SANS-SERIF SMALL Z �� LATIN SMALL LETTER Z#
			{120276, "A"},  // MA# ( ?? �� A ) MATHEMATICAL SANS-SERIF BOLD CAPITAL A �� LATIN CAPITAL LETTER A#
			{120277, "B"},  // MA# ( ?? �� B ) MATHEMATICAL SANS-SERIF BOLD CAPITAL B �� LATIN CAPITAL LETTER B#
			{120278, "C"},  // MA# ( ?? �� C ) MATHEMATICAL SANS-SERIF BOLD CAPITAL C �� LATIN CAPITAL LETTER C#
			{120279, "D"},  // MA# ( ?? �� D ) MATHEMATICAL SANS-SERIF BOLD CAPITAL D �� LATIN CAPITAL LETTER D#
			{120280, "E"},  // MA# ( ?? �� E ) MATHEMATICAL SANS-SERIF BOLD CAPITAL E �� LATIN CAPITAL LETTER E#
			{120281, "F"},  // MA# ( ?? �� F ) MATHEMATICAL SANS-SERIF BOLD CAPITAL F �� LATIN CAPITAL LETTER F#
			{120282, "G"},  // MA# ( ?? �� G ) MATHEMATICAL SANS-SERIF BOLD CAPITAL G �� LATIN CAPITAL LETTER G#
			{120283, "H"},  // MA# ( ?? �� H ) MATHEMATICAL SANS-SERIF BOLD CAPITAL H �� LATIN CAPITAL LETTER H#
			{120284, "l"},  // MA# ( ?? �� l ) MATHEMATICAL SANS-SERIF BOLD CAPITAL I �� LATIN SMALL LETTER L# ��I��
			{120285, "J"},  // MA# ( ?? �� J ) MATHEMATICAL SANS-SERIF BOLD CAPITAL J �� LATIN CAPITAL LETTER J#
			{120286, "K"},  // MA# ( ?? �� K ) MATHEMATICAL SANS-SERIF BOLD CAPITAL K �� LATIN CAPITAL LETTER K#
			{120287, "L"},  // MA# ( ?? �� L ) MATHEMATICAL SANS-SERIF BOLD CAPITAL L �� LATIN CAPITAL LETTER L#
			{120288, "M"},  // MA# ( ?? �� M ) MATHEMATICAL SANS-SERIF BOLD CAPITAL M �� LATIN CAPITAL LETTER M#
			{120289, "N"},  // MA# ( ?? �� N ) MATHEMATICAL SANS-SERIF BOLD CAPITAL N �� LATIN CAPITAL LETTER N#
			{120290, "O"},  // MA# ( ?? �� O ) MATHEMATICAL SANS-SERIF BOLD CAPITAL O �� LATIN CAPITAL LETTER O#
			{120291, "P"},  // MA# ( ?? �� P ) MATHEMATICAL SANS-SERIF BOLD CAPITAL P �� LATIN CAPITAL LETTER P#
			{120292, "Q"},  // MA# ( ?? �� Q ) MATHEMATICAL SANS-SERIF BOLD CAPITAL Q �� LATIN CAPITAL LETTER Q#
			{120293, "R"},  // MA# ( ?? �� R ) MATHEMATICAL SANS-SERIF BOLD CAPITAL R �� LATIN CAPITAL LETTER R#
			{120294, "S"},  // MA# ( ?? �� S ) MATHEMATICAL SANS-SERIF BOLD CAPITAL S �� LATIN CAPITAL LETTER S#
			{120295, "T"},  // MA# ( ?? �� T ) MATHEMATICAL SANS-SERIF BOLD CAPITAL T �� LATIN CAPITAL LETTER T#
			{120296, "U"},  // MA# ( ?? �� U ) MATHEMATICAL SANS-SERIF BOLD CAPITAL U �� LATIN CAPITAL LETTER U#
			{120297, "V"},  // MA# ( ?? �� V ) MATHEMATICAL SANS-SERIF BOLD CAPITAL V �� LATIN CAPITAL LETTER V#
			{120298, "W"},  // MA# ( ?? �� W ) MATHEMATICAL SANS-SERIF BOLD CAPITAL W �� LATIN CAPITAL LETTER W#
			{120299, "X"},  // MA# ( ?? �� X ) MATHEMATICAL SANS-SERIF BOLD CAPITAL X �� LATIN CAPITAL LETTER X#
			{120300, "Y"},  // MA# ( ?? �� Y ) MATHEMATICAL SANS-SERIF BOLD CAPITAL Y �� LATIN CAPITAL LETTER Y#
			{120301, "Z"},  // MA# ( ?? �� Z ) MATHEMATICAL SANS-SERIF BOLD CAPITAL Z �� LATIN CAPITAL LETTER Z#
			{120302, "a"},  // MA# ( ?? �� a ) MATHEMATICAL SANS-SERIF BOLD SMALL A �� LATIN SMALL LETTER A#
			{120303, "b"},  // MA# ( ?? �� b ) MATHEMATICAL SANS-SERIF BOLD SMALL B �� LATIN SMALL LETTER B#
			{120304, "c"},  // MA# ( ?? �� c ) MATHEMATICAL SANS-SERIF BOLD SMALL C �� LATIN SMALL LETTER C#
			{120305, "d"},  // MA# ( ?? �� d ) MATHEMATICAL SANS-SERIF BOLD SMALL D �� LATIN SMALL LETTER D#
			{120306, "e"},  // MA# ( ?? �� e ) MATHEMATICAL SANS-SERIF BOLD SMALL E �� LATIN SMALL LETTER E#
			{120307, "f"},  // MA# ( ?? �� f ) MATHEMATICAL SANS-SERIF BOLD SMALL F �� LATIN SMALL LETTER F#
			{120308, "g"},  // MA# ( ?? �� g ) MATHEMATICAL SANS-SERIF BOLD SMALL G �� LATIN SMALL LETTER G#
			{120309, "h"},  // MA# ( ?? �� h ) MATHEMATICAL SANS-SERIF BOLD SMALL H �� LATIN SMALL LETTER H#
			{120310, "i"},  // MA# ( ?? �� i ) MATHEMATICAL SANS-SERIF BOLD SMALL I �� LATIN SMALL LETTER I#
			{120311, "j"},  // MA# ( ?? �� j ) MATHEMATICAL SANS-SERIF BOLD SMALL J �� LATIN SMALL LETTER J#
			{120312, "k"},  // MA# ( ?? �� k ) MATHEMATICAL SANS-SERIF BOLD SMALL K �� LATIN SMALL LETTER K#
			{120313, "l"},  // MA# ( ?? �� l ) MATHEMATICAL SANS-SERIF BOLD SMALL L �� LATIN SMALL LETTER L#
			{120314, "rn"}, // MA# ( ?? �� rn ) MATHEMATICAL SANS-SERIF BOLD SMALL M �� LATIN SMALL LETTER R, LATIN SMALL LETTER N# ��m��
			{120315, "n"},  // MA# ( ?? �� n ) MATHEMATICAL SANS-SERIF BOLD SMALL N �� LATIN SMALL LETTER N#
			{120316, "o"},  // MA# ( ?? �� o ) MATHEMATICAL SANS-SERIF BOLD SMALL O �� LATIN SMALL LETTER O#
			{120317, "p"},  // MA# ( ?? �� p ) MATHEMATICAL SANS-SERIF BOLD SMALL P �� LATIN SMALL LETTER P#
			{120318, "q"},  // MA# ( ?? �� q ) MATHEMATICAL SANS-SERIF BOLD SMALL Q �� LATIN SMALL LETTER Q#
			{120319, "r"},  // MA# ( ?? �� r ) MATHEMATICAL SANS-SERIF BOLD SMALL R �� LATIN SMALL LETTER R#
			{120320, "s"},  // MA# ( ?? �� s ) MATHEMATICAL SANS-SERIF BOLD SMALL S �� LATIN SMALL LETTER S#
			{120321, "t"},  // MA# ( ?? �� t ) MATHEMATICAL SANS-SERIF BOLD SMALL T �� LATIN SMALL LETTER T#
			{120322, "u"},  // MA# ( ?? �� u ) MATHEMATICAL SANS-SERIF BOLD SMALL U �� LATIN SMALL LETTER U#
			{120323, "v"},  // MA# ( ?? �� v ) MATHEMATICAL SANS-SERIF BOLD SMALL V �� LATIN SMALL LETTER V#
			{120324, "w"},  // MA# ( ?? �� w ) MATHEMATICAL SANS-SERIF BOLD SMALL W �� LATIN SMALL LETTER W#
			{120325, "x"},  // MA# ( ?? �� x ) MATHEMATICAL SANS-SERIF BOLD SMALL X �� LATIN SMALL LETTER X#
			{120326, "y"},  // MA# ( ?? �� y ) MATHEMATICAL SANS-SERIF BOLD SMALL Y �� LATIN SMALL LETTER Y#
			{120327, "z"},  // MA# ( ?? �� z ) MATHEMATICAL SANS-SERIF BOLD SMALL Z �� LATIN SMALL LETTER Z#
			{120328, "A"},  // MA# ( ?? �� A ) MATHEMATICAL SANS-SERIF ITALIC CAPITAL A �� LATIN CAPITAL LETTER A#
			{120329, "B"},  // MA# ( ?? �� B ) MATHEMATICAL SANS-SERIF ITALIC CAPITAL B �� LATIN CAPITAL LETTER B#
			{120330, "C"},  // MA# ( ?? �� C ) MATHEMATICAL SANS-SERIF ITALIC CAPITAL C �� LATIN CAPITAL LETTER C#
			{120331, "D"},  // MA# ( ?? �� D ) MATHEMATICAL SANS-SERIF ITALIC CAPITAL D �� LATIN CAPITAL LETTER D#
			{120332, "E"},  // MA# ( ?? �� E ) MATHEMATICAL SANS-SERIF ITALIC CAPITAL E �� LATIN CAPITAL LETTER E#
			{120333, "F"},  // MA# ( ?? �� F ) MATHEMATICAL SANS-SERIF ITALIC CAPITAL F �� LATIN CAPITAL LETTER F#
			{120334, "G"},  // MA# ( ?? �� G ) MATHEMATICAL SANS-SERIF ITALIC CAPITAL G �� LATIN CAPITAL LETTER G#
			{120335, "H"},  // MA# ( ?? �� H ) MATHEMATICAL SANS-SERIF ITALIC CAPITAL H �� LATIN CAPITAL LETTER H#
			{120336, "l"},  // MA# ( ?? �� l ) MATHEMATICAL SANS-SERIF ITALIC CAPITAL I �� LATIN SMALL LETTER L# ��I��
			{120337, "J"},  // MA# ( ?? �� J ) MATHEMATICAL SANS-SERIF ITALIC CAPITAL J �� LATIN CAPITAL LETTER J#
			{120338, "K"},  // MA# ( ?? �� K ) MATHEMATICAL SANS-SERIF ITALIC CAPITAL K �� LATIN CAPITAL LETTER K#
			{120339, "L"},  // MA# ( ?? �� L ) MATHEMATICAL SANS-SERIF ITALIC CAPITAL L �� LATIN CAPITAL LETTER L#
			{120340, "M"},  // MA# ( ?? �� M ) MATHEMATICAL SANS-SERIF ITALIC CAPITAL M �� LATIN CAPITAL LETTER M#
			{120341, "N"},  // MA# ( ?? �� N ) MATHEMATICAL SANS-SERIF ITALIC CAPITAL N �� LATIN CAPITAL LETTER N#
			{120342, "O"},  // MA# ( ?? �� O ) MATHEMATICAL SANS-SERIF ITALIC CAPITAL O �� LATIN CAPITAL LETTER O#
			{120343, "P"},  // MA# ( ?? �� P ) MATHEMATICAL SANS-SERIF ITALIC CAPITAL P �� LATIN CAPITAL LETTER P#
			{120344, "Q"},  // MA# ( ?? �� Q ) MATHEMATICAL SANS-SERIF ITALIC CAPITAL Q �� LATIN CAPITAL LETTER Q#
			{120345, "R"},  // MA# ( ?? �� R ) MATHEMATICAL SANS-SERIF ITALIC CAPITAL R �� LATIN CAPITAL LETTER R#
			{120346, "S"},  // MA# ( ?? �� S ) MATHEMATICAL SANS-SERIF ITALIC CAPITAL S �� LATIN CAPITAL LETTER S#
			{120347, "T"},  // MA# ( ?? �� T ) MATHEMATICAL SANS-SERIF ITALIC CAPITAL T �� LATIN CAPITAL LETTER T#
			{120348, "U"},  // MA# ( ?? �� U ) MATHEMATICAL SANS-SERIF ITALIC CAPITAL U �� LATIN CAPITAL LETTER U#
			{120349, "V"},  // MA# ( ?? �� V ) MATHEMATICAL SANS-SERIF ITALIC CAPITAL V �� LATIN CAPITAL LETTER V#
			{120350, "W"},  // MA# ( ?? �� W ) MATHEMATICAL SANS-SERIF ITALIC CAPITAL W �� LATIN CAPITAL LETTER W#
			{120351, "X"},  // MA# ( ?? �� X ) MATHEMATICAL SANS-SERIF ITALIC CAPITAL X �� LATIN CAPITAL LETTER X#
			{120352, "Y"},  // MA# ( ?? �� Y ) MATHEMATICAL SANS-SERIF ITALIC CAPITAL Y �� LATIN CAPITAL LETTER Y#
			{120353, "Z"},  // MA# ( ?? �� Z ) MATHEMATICAL SANS-SERIF ITALIC CAPITAL Z �� LATIN CAPITAL LETTER Z#
			{120354, "a"},  // MA# ( ?? �� a ) MATHEMATICAL SANS-SERIF ITALIC SMALL A �� LATIN SMALL LETTER A#
			{120355, "b"},  // MA# ( ?? �� b ) MATHEMATICAL SANS-SERIF ITALIC SMALL B �� LATIN SMALL LETTER B#
			{120356, "c"},  // MA# ( ?? �� c ) MATHEMATICAL SANS-SERIF ITALIC SMALL C �� LATIN SMALL LETTER C#
			{120357, "d"},  // MA# ( ?? �� d ) MATHEMATICAL SANS-SERIF ITALIC SMALL D �� LATIN SMALL LETTER D#
			{120358, "e"},  // MA# ( ?? �� e ) MATHEMATICAL SANS-SERIF ITALIC SMALL E �� LATIN SMALL LETTER E#
			{120359, "f"},  // MA# ( ?? �� f ) MATHEMATICAL SANS-SERIF ITALIC SMALL F �� LATIN SMALL LETTER F#
			{120360, "g"},  // MA# ( ?? �� g ) MATHEMATICAL SANS-SERIF ITALIC SMALL G �� LATIN SMALL LETTER G#
			{120361, "h"},  // MA# ( ?? �� h ) MATHEMATICAL SANS-SERIF ITALIC SMALL H �� LATIN SMALL LETTER H#
			{120362, "i"},  // MA# ( ?? �� i ) MATHEMATICAL SANS-SERIF ITALIC SMALL I �� LATIN SMALL LETTER I#
			{120363, "j"},  // MA# ( ?? �� j ) MATHEMATICAL SANS-SERIF ITALIC SMALL J �� LATIN SMALL LETTER J#
			{120364, "k"},  // MA# ( ?? �� k ) MATHEMATICAL SANS-SERIF ITALIC SMALL K �� LATIN SMALL LETTER K#
			{120365, "l"},  // MA# ( ?? �� l ) MATHEMATICAL SANS-SERIF ITALIC SMALL L �� LATIN SMALL LETTER L#
			{120366, "rn"}, // MA# ( ?? �� rn ) MATHEMATICAL SANS-SERIF ITALIC SMALL M �� LATIN SMALL LETTER R, LATIN SMALL LETTER N# ��m��
			{120367, "n"},  // MA# ( ?? �� n ) MATHEMATICAL SANS-SERIF ITALIC SMALL N �� LATIN SMALL LETTER N#
			{120368, "o"},  // MA# ( ?? �� o ) MATHEMATICAL SANS-SERIF ITALIC SMALL O �� LATIN SMALL LETTER O#
			{120369, "p"},  // MA# ( ?? �� p ) MATHEMATICAL SANS-SERIF ITALIC SMALL P �� LATIN SMALL LETTER P#
			{120370, "q"},  // MA# ( ?? �� q ) MATHEMATICAL SANS-SERIF ITALIC SMALL Q �� LATIN SMALL LETTER Q#
			{120371, "r"},  // MA# ( ?? �� r ) MATHEMATICAL SANS-SERIF ITALIC SMALL R �� LATIN SMALL LETTER R#
			{120372, "s"},  // MA# ( ?? �� s ) MATHEMATICAL SANS-SERIF ITALIC SMALL S �� LATIN SMALL LETTER S#
			{120373, "t"},  // MA# ( ?? �� t ) MATHEMATICAL SANS-SERIF ITALIC SMALL T �� LATIN SMALL LETTER T#
			{120374, "u"},  // MA# ( ?? �� u ) MATHEMATICAL SANS-SERIF ITALIC SMALL U �� LATIN SMALL LETTER U#
			{120375, "v"},  // MA# ( ?? �� v ) MATHEMATICAL SANS-SERIF ITALIC SMALL V �� LATIN SMALL LETTER V#
			{120376, "w"},  // MA# ( ?? �� w ) MATHEMATICAL SANS-SERIF ITALIC SMALL W �� LATIN SMALL LETTER W#
			{120377, "x"},  // MA# ( ?? �� x ) MATHEMATICAL SANS-SERIF ITALIC SMALL X �� LATIN SMALL LETTER X#
			{120378, "y"},  // MA# ( ?? �� y ) MATHEMATICAL SANS-SERIF ITALIC SMALL Y �� LATIN SMALL LETTER Y#
			{120379, "z"},  // MA# ( ?? �� z ) MATHEMATICAL SANS-SERIF ITALIC SMALL Z �� LATIN SMALL LETTER Z#
			{120380, "A"},  // MA# ( ?? �� A ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL A �� LATIN CAPITAL LETTER A#
			{120381, "B"},  // MA# ( ?? �� B ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL B �� LATIN CAPITAL LETTER B#
			{120382, "C"},  // MA# ( ?? �� C ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL C �� LATIN CAPITAL LETTER C#
			{120383, "D"},  // MA# ( ?? �� D ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL D �� LATIN CAPITAL LETTER D#
			{120384, "E"},  // MA# ( ?? �� E ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL E �� LATIN CAPITAL LETTER E#
			{120385, "F"},  // MA# ( ?? �� F ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL F �� LATIN CAPITAL LETTER F#
			{120386, "G"},  // MA# ( ?? �� G ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL G �� LATIN CAPITAL LETTER G#
			{120387, "H"},  // MA# ( ?? �� H ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL H �� LATIN CAPITAL LETTER H#
			{120388, "l"},  // MA# ( ?? �� l ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL I �� LATIN SMALL LETTER L# ��I��
			{120389, "J"},  // MA# ( ?? �� J ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL J �� LATIN CAPITAL LETTER J#
			{120390, "K"},  // MA# ( ?? �� K ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL K �� LATIN CAPITAL LETTER K#
			{120391, "L"},  // MA# ( ?? �� L ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL L �� LATIN CAPITAL LETTER L#
			{120392, "M"},  // MA# ( ?? �� M ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL M �� LATIN CAPITAL LETTER M#
			{120393, "N"},  // MA# ( ?? �� N ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL N �� LATIN CAPITAL LETTER N#
			{120394, "O"},  // MA# ( ?? �� O ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL O �� LATIN CAPITAL LETTER O#
			{120395, "P"},  // MA# ( ?? �� P ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL P �� LATIN CAPITAL LETTER P#
			{120396, "Q"},  // MA# ( ?? �� Q ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL Q �� LATIN CAPITAL LETTER Q#
			{120397, "R"},  // MA# ( ?? �� R ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL R �� LATIN CAPITAL LETTER R#
			{120398, "S"},  // MA# ( ?? �� S ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL S �� LATIN CAPITAL LETTER S#
			{120399, "T"},  // MA# ( ?? �� T ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL T �� LATIN CAPITAL LETTER T#
			{120400, "U"},  // MA# ( ?? �� U ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL U �� LATIN CAPITAL LETTER U#
			{120401, "V"},  // MA# ( ?? �� V ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL V �� LATIN CAPITAL LETTER V#
			{120402, "W"},  // MA# ( ?? �� W ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL W �� LATIN CAPITAL LETTER W#
			{120403, "X"},  // MA# ( ?? �� X ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL X �� LATIN CAPITAL LETTER X#
			{120404, "Y"},  // MA# ( ?? �� Y ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL Y �� LATIN CAPITAL LETTER Y#
			{120405, "Z"},  // MA# ( ?? �� Z ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL Z �� LATIN CAPITAL LETTER Z#
			{120406, "a"},  // MA# ( ?? �� a ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL A �� LATIN SMALL LETTER A#
			{120407, "b"},  // MA# ( ?? �� b ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL B �� LATIN SMALL LETTER B#
			{120408, "c"},  // MA# ( ?? �� c ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL C �� LATIN SMALL LETTER C#
			{120409, "d"},  // MA# ( ?? �� d ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL D �� LATIN SMALL LETTER D#
			{120410, "e"},  // MA# ( ?? �� e ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL E �� LATIN SMALL LETTER E#
			{120411, "f"},  // MA# ( ?? �� f ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL F �� LATIN SMALL LETTER F#
			{120412, "g"},  // MA# ( ?? �� g ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL G �� LATIN SMALL LETTER G#
			{120413, "h"},  // MA# ( ?? �� h ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL H �� LATIN SMALL LETTER H#
			{120414, "i"},  // MA# ( ?? �� i ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL I �� LATIN SMALL LETTER I#
			{120415, "j"},  // MA# ( ?? �� j ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL J �� LATIN SMALL LETTER J#
			{120416, "k"},  // MA# ( ?? �� k ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL K �� LATIN SMALL LETTER K#
			{120417, "l"},  // MA# ( ?? �� l ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL L �� LATIN SMALL LETTER L#
			{120418, "rn"}, // MA# ( ?? �� rn ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL M �� LATIN SMALL LETTER R, LATIN SMALL LETTER N# ��m��
			{120419, "n"},  // MA# ( ?? �� n ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL N �� LATIN SMALL LETTER N#
			{120420, "o"},  // MA# ( ?? �� o ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL O �� LATIN SMALL LETTER O#
			{120421, "p"},  // MA# ( ?? �� p ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL P �� LATIN SMALL LETTER P#
			{120422, "q"},  // MA# ( ?? �� q ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL Q �� LATIN SMALL LETTER Q#
			{120423, "r"},  // MA# ( ?? �� r ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL R �� LATIN SMALL LETTER R#
			{120424, "s"},  // MA# ( ?? �� s ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL S �� LATIN SMALL LETTER S#
			{120425, "t"},  // MA# ( ?? �� t ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL T �� LATIN SMALL LETTER T#
			{120426, "u"},  // MA# ( ?? �� u ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL U �� LATIN SMALL LETTER U#
			{120427, "v"},  // MA# ( ?? �� v ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL V �� LATIN SMALL LETTER V#
			{120428, "w"},  // MA# ( ?? �� w ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL W �� LATIN SMALL LETTER W#
			{120429, "x"},  // MA# ( ?? �� x ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL X �� LATIN SMALL LETTER X#
			{120430, "y"},  // MA# ( ?? �� y ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL Y �� LATIN SMALL LETTER Y#
			{120431, "z"},  // MA# ( ?? �� z ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL Z �� LATIN SMALL LETTER Z#
			{120432, "A"},  // MA# ( ?? �� A ) MATHEMATICAL MONOSPACE CAPITAL A �� LATIN CAPITAL LETTER A#
			{120433, "B"},  // MA# ( ?? �� B ) MATHEMATICAL MONOSPACE CAPITAL B �� LATIN CAPITAL LETTER B#
			{120434, "C"},  // MA# ( ?? �� C ) MATHEMATICAL MONOSPACE CAPITAL C �� LATIN CAPITAL LETTER C#
			{120435, "D"},  // MA# ( ?? �� D ) MATHEMATICAL MONOSPACE CAPITAL D �� LATIN CAPITAL LETTER D#
			{120436, "E"},  // MA# ( ?? �� E ) MATHEMATICAL MONOSPACE CAPITAL E �� LATIN CAPITAL LETTER E#
			{120437, "F"},  // MA# ( ?? �� F ) MATHEMATICAL MONOSPACE CAPITAL F �� LATIN CAPITAL LETTER F#
			{120438, "G"},  // MA# ( ?? �� G ) MATHEMATICAL MONOSPACE CAPITAL G �� LATIN CAPITAL LETTER G#
			{120439, "H"},  // MA# ( ?? �� H ) MATHEMATICAL MONOSPACE CAPITAL H �� LATIN CAPITAL LETTER H#
			{120440, "l"},  // MA# ( ?? �� l ) MATHEMATICAL MONOSPACE CAPITAL I �� LATIN SMALL LETTER L# ��I��
			{120441, "J"},  // MA# ( ?? �� J ) MATHEMATICAL MONOSPACE CAPITAL J �� LATIN CAPITAL LETTER J#
			{120442, "K"},  // MA# ( ?? �� K ) MATHEMATICAL MONOSPACE CAPITAL K �� LATIN CAPITAL LETTER K#
			{120443, "L"},  // MA# ( ?? �� L ) MATHEMATICAL MONOSPACE CAPITAL L �� LATIN CAPITAL LETTER L#
			{120444, "M"},  // MA# ( ?? �� M ) MATHEMATICAL MONOSPACE CAPITAL M �� LATIN CAPITAL LETTER M#
			{120445, "N"},  // MA# ( ?? �� N ) MATHEMATICAL MONOSPACE CAPITAL N �� LATIN CAPITAL LETTER N#
			{120446, "O"},  // MA# ( ?? �� O ) MATHEMATICAL MONOSPACE CAPITAL O �� LATIN CAPITAL LETTER O#
			{120447, "P"},  // MA# ( ?? �� P ) MATHEMATICAL MONOSPACE CAPITAL P �� LATIN CAPITAL LETTER P#
			{120448, "Q"},  // MA# ( ?? �� Q ) MATHEMATICAL MONOSPACE CAPITAL Q �� LATIN CAPITAL LETTER Q#
			{120449, "R"},  // MA# ( ?? �� R ) MATHEMATICAL MONOSPACE CAPITAL R �� LATIN CAPITAL LETTER R#
			{120450, "S"},  // MA# ( ?? �� S ) MATHEMATICAL MONOSPACE CAPITAL S �� LATIN CAPITAL LETTER S#
			{120451, "T"},  // MA# ( ?? �� T ) MATHEMATICAL MONOSPACE CAPITAL T �� LATIN CAPITAL LETTER T#
			{120452, "U"},  // MA# ( ?? �� U ) MATHEMATICAL MONOSPACE CAPITAL U �� LATIN CAPITAL LETTER U#
			{120453, "V"},  // MA# ( ?? �� V ) MATHEMATICAL MONOSPACE CAPITAL V �� LATIN CAPITAL LETTER V#
			{120454, "W"},  // MA# ( ?? �� W ) MATHEMATICAL MONOSPACE CAPITAL W �� LATIN CAPITAL LETTER W#
			{120455, "X"},  // MA# ( ?? �� X ) MATHEMATICAL MONOSPACE CAPITAL X �� LATIN CAPITAL LETTER X#
			{120456, "Y"},  // MA# ( ?? �� Y ) MATHEMATICAL MONOSPACE CAPITAL Y �� LATIN CAPITAL LETTER Y#
			{120457, "Z"},  // MA# ( ?? �� Z ) MATHEMATICAL MONOSPACE CAPITAL Z �� LATIN CAPITAL LETTER Z#
			{120458, "a"},  // MA# ( ?? �� a ) MATHEMATICAL MONOSPACE SMALL A �� LATIN SMALL LETTER A#
			{120459, "b"},  // MA# ( ?? �� b ) MATHEMATICAL MONOSPACE SMALL B �� LATIN SMALL LETTER B#
			{120460, "c"},  // MA# ( ?? �� c ) MATHEMATICAL MONOSPACE SMALL C �� LATIN SMALL LETTER C#
			{120461, "d"},  // MA# ( ?? �� d ) MATHEMATICAL MONOSPACE SMALL D �� LATIN SMALL LETTER D#
			{120462, "e"},  // MA# ( ?? �� e ) MATHEMATICAL MONOSPACE SMALL E �� LATIN SMALL LETTER E#
			{120463, "f"},  // MA# ( ?? �� f ) MATHEMATICAL MONOSPACE SMALL F �� LATIN SMALL LETTER F#
			{120464, "g"},  // MA# ( ?? �� g ) MATHEMATICAL MONOSPACE SMALL G �� LATIN SMALL LETTER G#
			{120465, "h"},  // MA# ( ?? �� h ) MATHEMATICAL MONOSPACE SMALL H �� LATIN SMALL LETTER H#
			{120466, "i"},  // MA# ( ?? �� i ) MATHEMATICAL MONOSPACE SMALL I �� LATIN SMALL LETTER I#
			{120467, "j"},  // MA# ( ?? �� j ) MATHEMATICAL MONOSPACE SMALL J �� LATIN SMALL LETTER J#
			{120468, "k"},  // MA# ( ?? �� k ) MATHEMATICAL MONOSPACE SMALL K �� LATIN SMALL LETTER K#
			{120469, "l"},  // MA# ( ?? �� l ) MATHEMATICAL MONOSPACE SMALL L �� LATIN SMALL LETTER L#
			{120470, "rn"}, // MA# ( ?? �� rn ) MATHEMATICAL MONOSPACE SMALL M �� LATIN SMALL LETTER R, LATIN SMALL LETTER N# ��m��
			{120471, "n"},  // MA# ( ?? �� n ) MATHEMATICAL MONOSPACE SMALL N �� LATIN SMALL LETTER N#
			{120472, "o"},  // MA# ( ?? �� o ) MATHEMATICAL MONOSPACE SMALL O �� LATIN SMALL LETTER O#
			{120473, "p"},  // MA# ( ?? �� p ) MATHEMATICAL MONOSPACE SMALL P �� LATIN SMALL LETTER P#
			{120474, "q"},  // MA# ( ?? �� q ) MATHEMATICAL MONOSPACE SMALL Q �� LATIN SMALL LETTER Q#
			{120475, "r"},  // MA# ( ?? �� r ) MATHEMATICAL MONOSPACE SMALL R �� LATIN SMALL LETTER R#
			{120476, "s"},  // MA# ( ?? �� s ) MATHEMATICAL MONOSPACE SMALL S �� LATIN SMALL LETTER S#
			{120477, "t"},  // MA# ( ?? �� t ) MATHEMATICAL MONOSPACE SMALL T �� LATIN SMALL LETTER T#
			{120478, "u"},  // MA# ( ?? �� u ) MATHEMATICAL MONOSPACE SMALL U �� LATIN SMALL LETTER U#
			{120479, "v"},  // MA# ( ?? �� v ) MATHEMATICAL MONOSPACE SMALL V �� LATIN SMALL LETTER V#
			{120480, "w"},  // MA# ( ?? �� w ) MATHEMATICAL MONOSPACE SMALL W �� LATIN SMALL LETTER W#
			{120481, "x"},  // MA# ( ?? �� x ) MATHEMATICAL MONOSPACE SMALL X �� LATIN SMALL LETTER X#
			{120482, "y"},  // MA# ( ?? �� y ) MATHEMATICAL MONOSPACE SMALL Y �� LATIN SMALL LETTER Y#
			{120483, "z"},  // MA# ( ?? �� z ) MATHEMATICAL MONOSPACE SMALL Z �� LATIN SMALL LETTER Z#
			{120484, "i"},  // MA# ( ?? �� i ) MATHEMATICAL ITALIC SMALL DOTLESS I �� LATIN SMALL LETTER I# ��?��
			{120488, "A"},  // MA# ( ?? �� A ) MATHEMATICAL BOLD CAPITAL ALPHA �� LATIN CAPITAL LETTER A# ��??��
			{120489, "B"},  // MA# ( ?? �� B ) MATHEMATICAL BOLD CAPITAL BETA �� LATIN CAPITAL LETTER B# ������
			{120492, "E"},  // MA# ( ?? �� E ) MATHEMATICAL BOLD CAPITAL EPSILON �� LATIN CAPITAL LETTER E# ��??��
			{120493, "Z"},  // MA# ( ?? �� Z ) MATHEMATICAL BOLD CAPITAL ZETA �� LATIN CAPITAL LETTER Z# ������
			{120494, "H"},  // MA# ( ?? �� H ) MATHEMATICAL BOLD CAPITAL ETA �� LATIN CAPITAL LETTER H# ������
			{120496, "l"},  // MA# ( ?? �� l ) MATHEMATICAL BOLD CAPITAL IOTA �� LATIN SMALL LETTER L# ������
			{120497, "K"},  // MA# ( ?? �� K ) MATHEMATICAL BOLD CAPITAL KAPPA �� LATIN CAPITAL LETTER K# ������
			{120499, "M"},  // MA# ( ?? �� M ) MATHEMATICAL BOLD CAPITAL MU �� LATIN CAPITAL LETTER M# ��??��
			{120500, "N"},  // MA# ( ?? �� N ) MATHEMATICAL BOLD CAPITAL NU �� LATIN CAPITAL LETTER N# ��??��
			{120502, "O"},  // MA# ( ?? �� O ) MATHEMATICAL BOLD CAPITAL OMICRON �� LATIN CAPITAL LETTER O# ��??��
			{120504, "P"},  // MA# ( ?? �� P ) MATHEMATICAL BOLD CAPITAL RHO �� LATIN CAPITAL LETTER P# ��??��
			{120507, "T"},  // MA# ( ?? �� T ) MATHEMATICAL BOLD CAPITAL TAU �� LATIN CAPITAL LETTER T# ������
			{120508, "Y"},  // MA# ( ?? �� Y ) MATHEMATICAL BOLD CAPITAL UPSILON �� LATIN CAPITAL LETTER Y# ������
			{120510, "X"},  // MA# ( ?? �� X ) MATHEMATICAL BOLD CAPITAL CHI �� LATIN CAPITAL LETTER X# ������
			{120514, "a"},  // MA# ( ?? �� a ) MATHEMATICAL BOLD SMALL ALPHA �� LATIN SMALL LETTER A# ������
			{120516, "y"},  // MA# ( ?? �� y ) MATHEMATICAL BOLD SMALL GAMMA �� LATIN SMALL LETTER Y# ���á�
			{120522, "i"},  // MA# ( ?? �� i ) MATHEMATICAL BOLD SMALL IOTA �� LATIN SMALL LETTER I# ���ɡ�
			{120526, "v"},  // MA# ( ?? �� v ) MATHEMATICAL BOLD SMALL NU �� LATIN SMALL LETTER V# ���͡�
			{120528, "o"},  // MA# ( ?? �� o ) MATHEMATICAL BOLD SMALL OMICRON �� LATIN SMALL LETTER O# ��??��
			{120530, "p"},  // MA# ( ?? �� p ) MATHEMATICAL BOLD SMALL RHO �� LATIN SMALL LETTER P# ���ѡ�
			{120532, "o"},  // MA# ( ?? �� o ) MATHEMATICAL BOLD SMALL SIGMA �� LATIN SMALL LETTER O# ���ҡ�
			{120534, "u"},  // MA# ( ?? �� u ) MATHEMATICAL BOLD SMALL UPSILON �� LATIN SMALL LETTER U# ���ԡ���?��
			{120544, "p"},  // MA# ( ?? �� p ) MATHEMATICAL BOLD RHO SYMBOL �� LATIN SMALL LETTER P# ���ѡ�
			{120546, "A"},  // MA# ( ?? �� A ) MATHEMATICAL ITALIC CAPITAL ALPHA �� LATIN CAPITAL LETTER A# ������
			{120547, "B"},  // MA# ( ?? �� B ) MATHEMATICAL ITALIC CAPITAL BETA �� LATIN CAPITAL LETTER B# ������
			{120550, "E"},  // MA# ( ?? �� E ) MATHEMATICAL ITALIC CAPITAL EPSILON �� LATIN CAPITAL LETTER E# ������
			{120551, "Z"},  // MA# ( ?? �� Z ) MATHEMATICAL ITALIC CAPITAL ZETA �� LATIN CAPITAL LETTER Z# ��??��
			{120552, "H"},  // MA# ( ?? �� H ) MATHEMATICAL ITALIC CAPITAL ETA �� LATIN CAPITAL LETTER H# ������
			{120554, "l"},  // MA# ( ?? �� l ) MATHEMATICAL ITALIC CAPITAL IOTA �� LATIN SMALL LETTER L# ������
			{120555, "K"},  // MA# ( ?? �� K ) MATHEMATICAL ITALIC CAPITAL KAPPA �� LATIN CAPITAL LETTER K# ��??��
			{120557, "M"},  // MA# ( ?? �� M ) MATHEMATICAL ITALIC CAPITAL MU �� LATIN CAPITAL LETTER M# ��??��
			{120558, "N"},  // MA# ( ?? �� N ) MATHEMATICAL ITALIC CAPITAL NU �� LATIN CAPITAL LETTER N# ��??��
			{120560, "O"},  // MA# ( ?? �� O ) MATHEMATICAL ITALIC CAPITAL OMICRON �� LATIN CAPITAL LETTER O# ��??��
			{120562, "P"},  // MA# ( ?? �� P ) MATHEMATICAL ITALIC CAPITAL RHO �� LATIN CAPITAL LETTER P# ������
			{120565, "T"},  // MA# ( ?? �� T ) MATHEMATICAL ITALIC CAPITAL TAU �� LATIN CAPITAL LETTER T# ������
			{120566, "Y"},  // MA# ( ?? �� Y ) MATHEMATICAL ITALIC CAPITAL UPSILON �� LATIN CAPITAL LETTER Y# ������
			{120568, "X"},  // MA# ( ?? �� X ) MATHEMATICAL ITALIC CAPITAL CHI �� LATIN CAPITAL LETTER X# ������
			{120572, "a"},  // MA# ( ?? �� a ) MATHEMATICAL ITALIC SMALL ALPHA �� LATIN SMALL LETTER A# ������
			{120574, "y"},  // MA# ( ?? �� y ) MATHEMATICAL ITALIC SMALL GAMMA �� LATIN SMALL LETTER Y# ���á�
			{120580, "i"},  // MA# ( ?? �� i ) MATHEMATICAL ITALIC SMALL IOTA �� LATIN SMALL LETTER I# ���ɡ�
			{120584, "v"},  // MA# ( ?? �� v ) MATHEMATICAL ITALIC SMALL NU �� LATIN SMALL LETTER V# ���͡�
			{120586, "o"},  // MA# ( ?? �� o ) MATHEMATICAL ITALIC SMALL OMICRON �� LATIN SMALL LETTER O# ��??��
			{120588, "p"},  // MA# ( ?? �� p ) MATHEMATICAL ITALIC SMALL RHO �� LATIN SMALL LETTER P# ���ѡ�
			{120590, "o"},  // MA# ( ?? �� o ) MATHEMATICAL ITALIC SMALL SIGMA �� LATIN SMALL LETTER O# ���ҡ�
			{120592, "u"},  // MA# ( ?? �� u ) MATHEMATICAL ITALIC SMALL UPSILON �� LATIN SMALL LETTER U# ���ԡ���?��
			{120602, "p"},  // MA# ( ?? �� p ) MATHEMATICAL ITALIC RHO SYMBOL �� LATIN SMALL LETTER P# ���ѡ�
			{120604, "A"},  // MA# ( ?? �� A ) MATHEMATICAL BOLD ITALIC CAPITAL ALPHA �� LATIN CAPITAL LETTER A# ������
			{120605, "B"},  // MA# ( ?? �� B ) MATHEMATICAL BOLD ITALIC CAPITAL BETA �� LATIN CAPITAL LETTER B# ������
			{120608, "E"},  // MA# ( ?? �� E ) MATHEMATICAL BOLD ITALIC CAPITAL EPSILON �� LATIN CAPITAL LETTER E# ������
			{120609, "Z"},  // MA# ( ?? �� Z ) MATHEMATICAL BOLD ITALIC CAPITAL ZETA �� LATIN CAPITAL LETTER Z# ������
			{120610, "H"},  // MA# ( ?? �� H ) MATHEMATICAL BOLD ITALIC CAPITAL ETA �� LATIN CAPITAL LETTER H# ��??��
			{120612, "l"},  // MA# ( ?? �� l ) MATHEMATICAL BOLD ITALIC CAPITAL IOTA �� LATIN SMALL LETTER L# ������
			{120613, "K"},  // MA# ( ?? �� K ) MATHEMATICAL BOLD ITALIC CAPITAL KAPPA �� LATIN CAPITAL LETTER K# ��??��
			{120615, "M"},  // MA# ( ?? �� M ) MATHEMATICAL BOLD ITALIC CAPITAL MU �� LATIN CAPITAL LETTER M# ��??��
			{120616, "N"},  // MA# ( ?? �� N ) MATHEMATICAL BOLD ITALIC CAPITAL NU �� LATIN CAPITAL LETTER N# ��??��
			{120618, "O"},  // MA# ( ?? �� O ) MATHEMATICAL BOLD ITALIC CAPITAL OMICRON �� LATIN CAPITAL LETTER O# ��??��
			{120620, "P"},  // MA# ( ?? �� P ) MATHEMATICAL BOLD ITALIC CAPITAL RHO �� LATIN CAPITAL LETTER P# ������
			{120623, "T"},  // MA# ( ?? �� T ) MATHEMATICAL BOLD ITALIC CAPITAL TAU �� LATIN CAPITAL LETTER T# ������
			{120624, "Y"},  // MA# ( ?? �� Y ) MATHEMATICAL BOLD ITALIC CAPITAL UPSILON �� LATIN CAPITAL LETTER Y# ������
			{120626, "X"},  // MA# ( ?? �� X ) MATHEMATICAL BOLD ITALIC CAPITAL CHI �� LATIN CAPITAL LETTER X# ��??��
			{120630, "a"},  // MA# ( ?? �� a ) MATHEMATICAL BOLD ITALIC SMALL ALPHA �� LATIN SMALL LETTER A# ������
			{120632, "y"},  // MA# ( ?? �� y ) MATHEMATICAL BOLD ITALIC SMALL GAMMA �� LATIN SMALL LETTER Y# ���á�
			{120638, "i"},  // MA# ( ?? �� i ) MATHEMATICAL BOLD ITALIC SMALL IOTA �� LATIN SMALL LETTER I# ���ɡ�
			{120642, "v"},  // MA# ( ?? �� v ) MATHEMATICAL BOLD ITALIC SMALL NU �� LATIN SMALL LETTER V# ���͡�
			{120644, "o"},  // MA# ( ?? �� o ) MATHEMATICAL BOLD ITALIC SMALL OMICRON �� LATIN SMALL LETTER O# ��??��
			{120646, "p"},  // MA# ( ?? �� p ) MATHEMATICAL BOLD ITALIC SMALL RHO �� LATIN SMALL LETTER P# ���ѡ�
			{120648, "o"},  // MA# ( ?? �� o ) MATHEMATICAL BOLD ITALIC SMALL SIGMA �� LATIN SMALL LETTER O# ���ҡ�
			{120650, "u"},  // MA# ( ?? �� u ) MATHEMATICAL BOLD ITALIC SMALL UPSILON �� LATIN SMALL LETTER U# ���ԡ���?��
			{120660, "p"},  // MA# ( ?? �� p ) MATHEMATICAL BOLD ITALIC RHO SYMBOL �� LATIN SMALL LETTER P# ���ѡ�
			{120662, "A"},  // MA# ( ?? �� A ) MATHEMATICAL SANS-SERIF BOLD CAPITAL ALPHA �� LATIN CAPITAL LETTER A# ������
			{120663, "B"},  // MA# ( ?? �� B ) MATHEMATICAL SANS-SERIF BOLD CAPITAL BETA �� LATIN CAPITAL LETTER B# ������
			{120666, "E"},  // MA# ( ?? �� E ) MATHEMATICAL SANS-SERIF BOLD CAPITAL EPSILON �� LATIN CAPITAL LETTER E# ������
			{120667, "Z"},  // MA# ( ?? �� Z ) MATHEMATICAL SANS-SERIF BOLD CAPITAL ZETA �� LATIN CAPITAL LETTER Z# ������
			{120668, "H"},  // MA# ( ?? �� H ) MATHEMATICAL SANS-SERIF BOLD CAPITAL ETA �� LATIN CAPITAL LETTER H# ������
			{120670, "l"},  // MA# ( ?? �� l ) MATHEMATICAL SANS-SERIF BOLD CAPITAL IOTA �� LATIN SMALL LETTER L# ������
			{120671, "K"},  // MA# ( ?? �� K ) MATHEMATICAL SANS-SERIF BOLD CAPITAL KAPPA �� LATIN CAPITAL LETTER K# ������
			{120673, "M"},  // MA# ( ?? �� M ) MATHEMATICAL SANS-SERIF BOLD CAPITAL MU �� LATIN CAPITAL LETTER M# ������
			{120674, "N"},  // MA# ( ?? �� N ) MATHEMATICAL SANS-SERIF BOLD CAPITAL NU �� LATIN CAPITAL LETTER N# ������
			{120676, "O"},  // MA# ( ?? �� O ) MATHEMATICAL SANS-SERIF BOLD CAPITAL OMICRON �� LATIN CAPITAL LETTER O# ������
			{120678, "P"},  // MA# ( ?? �� P ) MATHEMATICAL SANS-SERIF BOLD CAPITAL RHO �� LATIN CAPITAL LETTER P# ������
			{120681, "T"},  // MA# ( ?? �� T ) MATHEMATICAL SANS-SERIF BOLD CAPITAL TAU �� LATIN CAPITAL LETTER T# ������
			{120682, "Y"},  // MA# ( ?? �� Y ) MATHEMATICAL SANS-SERIF BOLD CAPITAL UPSILON �� LATIN CAPITAL LETTER Y# ������
			{120684, "X"},  // MA# ( ?? �� X ) MATHEMATICAL SANS-SERIF BOLD CAPITAL CHI �� LATIN CAPITAL LETTER X# ������
			{120688, "a"},  // MA# ( ?? �� a ) MATHEMATICAL SANS-SERIF BOLD SMALL ALPHA �� LATIN SMALL LETTER A# ������
			{120690, "y"},  // MA# ( ?? �� y ) MATHEMATICAL SANS-SERIF BOLD SMALL GAMMA �� LATIN SMALL LETTER Y# ���á�
			{120696, "i"},  // MA# ( ?? �� i ) MATHEMATICAL SANS-SERIF BOLD SMALL IOTA �� LATIN SMALL LETTER I# ���ɡ�
			{120700, "v"},  // MA# ( ?? �� v ) MATHEMATICAL SANS-SERIF BOLD SMALL NU �� LATIN SMALL LETTER V# ���͡�
			{120702, "o"},  // MA# ( ?? �� o ) MATHEMATICAL SANS-SERIF BOLD SMALL OMICRON �� LATIN SMALL LETTER O# ���ϡ�
			{120704, "p"},  // MA# ( ?? �� p ) MATHEMATICAL SANS-SERIF BOLD SMALL RHO �� LATIN SMALL LETTER P# ���ѡ�
			{120706, "o"},  // MA# ( ?? �� o ) MATHEMATICAL SANS-SERIF BOLD SMALL SIGMA �� LATIN SMALL LETTER O# ���ҡ�
			{120708, "u"},  // MA# ( ?? �� u ) MATHEMATICAL SANS-SERIF BOLD SMALL UPSILON �� LATIN SMALL LETTER U# ���ԡ���?��
			{120718, "p"},  // MA# ( ?? �� p ) MATHEMATICAL SANS-SERIF BOLD RHO SYMBOL �� LATIN SMALL LETTER P# ���ѡ�
			{120720, "A"},  // MA# ( ?? �� A ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL ALPHA �� LATIN CAPITAL LETTER A# ������
			{120721, "B"},  // MA# ( ?? �� B ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL BETA �� LATIN CAPITAL LETTER B# ������
			{120724, "E"},  // MA# ( ?? �� E ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL EPSILON �� LATIN CAPITAL LETTER E# ������
			{120725, "Z"},  // MA# ( ?? �� Z ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL ZETA �� LATIN CAPITAL LETTER Z# ������
			{120726, "H"},  // MA# ( ?? �� H ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL ETA �� LATIN CAPITAL LETTER H# ������
			{120728, "l"},  // MA# ( ?? �� l ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL IOTA �� LATIN SMALL LETTER L# ������
			{120729, "K"},  // MA# ( ?? �� K ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL KAPPA �� LATIN CAPITAL LETTER K# ������
			{120731, "M"},  // MA# ( ?? �� M ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL MU �� LATIN CAPITAL LETTER M# ������
			{120732, "N"},  // MA# ( ?? �� N ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL NU �� LATIN CAPITAL LETTER N# ������
			{120734, "O"},  // MA# ( ?? �� O ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL OMICRON �� LATIN CAPITAL LETTER O# ������
			{120736, "P"},  // MA# ( ?? �� P ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL RHO �� LATIN CAPITAL LETTER P# ������
			{120739, "T"},  // MA# ( ?? �� T ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL TAU �� LATIN CAPITAL LETTER T# ������
			{120740, "Y"},  // MA# ( ?? �� Y ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL UPSILON �� LATIN CAPITAL LETTER Y# ������
			{120742, "X"},  // MA# ( ?? �� X ) MATHEMATICAL SANS-SERIF BOLD ITALIC CAPITAL CHI �� LATIN CAPITAL LETTER X# ������
			{120746, "a"},  // MA# ( ?? �� a ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL ALPHA �� LATIN SMALL LETTER A# ������
			{120748, "y"},  // MA# ( ?? �� y ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL GAMMA �� LATIN SMALL LETTER Y# ���á�
			{120754, "i"},  // MA# ( ?? �� i ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL IOTA �� LATIN SMALL LETTER I# ���ɡ�
			{120758, "v"},  // MA# ( ?? �� v ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL NU �� LATIN SMALL LETTER V# ���͡�
			{120760, "o"},  // MA# ( ?? �� o ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL OMICRON �� LATIN SMALL LETTER O# ���ϡ�
			{120762, "p"},  // MA# ( ?? �� p ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL RHO �� LATIN SMALL LETTER P# ���ѡ�
			{120764, "o"},  // MA# ( ?? �� o ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL SIGMA �� LATIN SMALL LETTER O# ���ҡ�
			{120766, "u"},  // MA# ( ?? �� u ) MATHEMATICAL SANS-SERIF BOLD ITALIC SMALL UPSILON �� LATIN SMALL LETTER U# ���ԡ���?��
			{120776, "p"},  // MA# ( ?? �� p ) MATHEMATICAL SANS-SERIF BOLD ITALIC RHO SYMBOL �� LATIN SMALL LETTER P# ���ѡ�
			{120778, "F"},  // MA# ( ?? �� F ) MATHEMATICAL BOLD CAPITAL DIGAMMA �� LATIN CAPITAL LETTER F# ��?��
			{120782, "O"},  // MA# ( ?? �� O ) MATHEMATICAL BOLD DIGIT ZERO �� LATIN CAPITAL LETTER O# ��0��
			{120783, "l"},  // MA# ( ?? �� l ) MATHEMATICAL BOLD DIGIT ONE �� LATIN SMALL LETTER L# ��1��
			{120784, "2"},  // MA# ( ?? �� 2 ) MATHEMATICAL BOLD DIGIT TWO �� DIGIT TWO#
			{120785, "3"},  // MA# ( ?? �� 3 ) MATHEMATICAL BOLD DIGIT THREE �� DIGIT THREE#
			{120786, "4"},  // MA# ( ?? �� 4 ) MATHEMATICAL BOLD DIGIT FOUR �� DIGIT FOUR#
			{120787, "5"},  // MA# ( ?? �� 5 ) MATHEMATICAL BOLD DIGIT FIVE �� DIGIT FIVE#
			{120788, "6"},  // MA# ( ?? �� 6 ) MATHEMATICAL BOLD DIGIT SIX �� DIGIT SIX#
			{120789, "7"},  // MA# ( ?? �� 7 ) MATHEMATICAL BOLD DIGIT SEVEN �� DIGIT SEVEN#
			{120790, "8"},  // MA# ( ?? �� 8 ) MATHEMATICAL BOLD DIGIT EIGHT �� DIGIT EIGHT#
			{120791, "9"},  // MA# ( ?? �� 9 ) MATHEMATICAL BOLD DIGIT NINE �� DIGIT NINE#
			{120792, "O"},  // MA# ( ?? �� O ) MATHEMATICAL DOUBLE-STRUCK DIGIT ZERO �� LATIN CAPITAL LETTER O# ��0��
			{120793, "l"},  // MA# ( ?? �� l ) MATHEMATICAL DOUBLE-STRUCK DIGIT ONE �� LATIN SMALL LETTER L# ��1��
			{120794, "2"},  // MA# ( ?? �� 2 ) MATHEMATICAL DOUBLE-STRUCK DIGIT TWO �� DIGIT TWO#
			{120795, "3"},  // MA# ( ?? �� 3 ) MATHEMATICAL DOUBLE-STRUCK DIGIT THREE �� DIGIT THREE#
			{120796, "4"},  // MA# ( ?? �� 4 ) MATHEMATICAL DOUBLE-STRUCK DIGIT FOUR �� DIGIT FOUR#
			{120797, "5"},  // MA# ( ?? �� 5 ) MATHEMATICAL DOUBLE-STRUCK DIGIT FIVE �� DIGIT FIVE#
			{120798, "6"},  // MA# ( ?? �� 6 ) MATHEMATICAL DOUBLE-STRUCK DIGIT SIX �� DIGIT SIX#
			{120799, "7"},  // MA# ( ?? �� 7 ) MATHEMATICAL DOUBLE-STRUCK DIGIT SEVEN �� DIGIT SEVEN#
			{120800, "8"},  // MA# ( ?? �� 8 ) MATHEMATICAL DOUBLE-STRUCK DIGIT EIGHT �� DIGIT EIGHT#
			{120801, "9"},  // MA# ( ?? �� 9 ) MATHEMATICAL DOUBLE-STRUCK DIGIT NINE �� DIGIT NINE#
			{120802, "O"},  // MA# ( ?? �� O ) MATHEMATICAL SANS-SERIF DIGIT ZERO �� LATIN CAPITAL LETTER O# ��0��
			{120803, "l"},  // MA# ( ?? �� l ) MATHEMATICAL SANS-SERIF DIGIT ONE �� LATIN SMALL LETTER L# ��1��
			{120804, "2"},  // MA# ( ?? �� 2 ) MATHEMATICAL SANS-SERIF DIGIT TWO �� DIGIT TWO#
			{120805, "3"},  // MA# ( ?? �� 3 ) MATHEMATICAL SANS-SERIF DIGIT THREE �� DIGIT THREE#
			{120806, "4"},  // MA# ( ?? �� 4 ) MATHEMATICAL SANS-SERIF DIGIT FOUR �� DIGIT FOUR#
			{120807, "5"},  // MA# ( ?? �� 5 ) MATHEMATICAL SANS-SERIF DIGIT FIVE �� DIGIT FIVE#
			{120808, "6"},  // MA# ( ?? �� 6 ) MATHEMATICAL SANS-SERIF DIGIT SIX �� DIGIT SIX#
			{120809, "7"},  // MA# ( ?? �� 7 ) MATHEMATICAL SANS-SERIF DIGIT SEVEN �� DIGIT SEVEN#
			{120810, "8"},  // MA# ( ?? �� 8 ) MATHEMATICAL SANS-SERIF DIGIT EIGHT �� DIGIT EIGHT#
			{120811, "9"},  // MA# ( ?? �� 9 ) MATHEMATICAL SANS-SERIF DIGIT NINE �� DIGIT NINE#
			{120812, "O"},  // MA# ( ?? �� O ) MATHEMATICAL SANS-SERIF BOLD DIGIT ZERO �� LATIN CAPITAL LETTER O# ��0��
			{120813, "l"},  // MA# ( ?? �� l ) MATHEMATICAL SANS-SERIF BOLD DIGIT ONE �� LATIN SMALL LETTER L# ��1��
			{120814, "2"},  // MA# ( ?? �� 2 ) MATHEMATICAL SANS-SERIF BOLD DIGIT TWO �� DIGIT TWO#
			{120815, "3"},  // MA# ( ?? �� 3 ) MATHEMATICAL SANS-SERIF BOLD DIGIT THREE �� DIGIT THREE#
			{120816, "4"},  // MA# ( ?? �� 4 ) MATHEMATICAL SANS-SERIF BOLD DIGIT FOUR �� DIGIT FOUR#
			{120817, "5"},  // MA# ( ?? �� 5 ) MATHEMATICAL SANS-SERIF BOLD DIGIT FIVE �� DIGIT FIVE#
			{120818, "6"},  // MA# ( ?? �� 6 ) MATHEMATICAL SANS-SERIF BOLD DIGIT SIX �� DIGIT SIX#
			{120819, "7"},  // MA# ( ?? �� 7 ) MATHEMATICAL SANS-SERIF BOLD DIGIT SEVEN �� DIGIT SEVEN#
			{120820, "8"},  // MA# ( ?? �� 8 ) MATHEMATICAL SANS-SERIF BOLD DIGIT EIGHT �� DIGIT EIGHT#
			{120821, "9"},  // MA# ( ?? �� 9 ) MATHEMATICAL SANS-SERIF BOLD DIGIT NINE �� DIGIT NINE#
			{120822, "O"},  // MA# ( ?? �� O ) MATHEMATICAL MONOSPACE DIGIT ZERO �� LATIN CAPITAL LETTER O# ��0��
			{120823, "l"},  // MA# ( ?? �� l ) MATHEMATICAL MONOSPACE DIGIT ONE �� LATIN SMALL LETTER L# ��1��
			{120824, "2"},  // MA# ( ?? �� 2 ) MATHEMATICAL MONOSPACE DIGIT TWO �� DIGIT TWO#
			{120825, "3"},  // MA# ( ?? �� 3 ) MATHEMATICAL MONOSPACE DIGIT THREE �� DIGIT THREE#
			{120826, "4"},  // MA# ( ?? �� 4 ) MATHEMATICAL MONOSPACE DIGIT FOUR �� DIGIT FOUR#
			{120827, "5"},  // MA# ( ?? �� 5 ) MATHEMATICAL MONOSPACE DIGIT FIVE �� DIGIT FIVE#
			{120828, "6"},  // MA# ( ?? �� 6 ) MATHEMATICAL MONOSPACE DIGIT SIX �� DIGIT SIX#
			{120829, "7"},  // MA# ( ?? �� 7 ) MATHEMATICAL MONOSPACE DIGIT SEVEN �� DIGIT SEVEN#
			{120830, "8"},  // MA# ( ?? �� 8 ) MATHEMATICAL MONOSPACE DIGIT EIGHT �� DIGIT EIGHT#
			{120831, "9"},  // MA# ( ?? �� 9 ) MATHEMATICAL MONOSPACE DIGIT NINE �� DIGIT NINE#
			{125127, "l"},  // MA#* ( ???? �� l ) MENDE KIKAKUI DIGIT ONE �� LATIN SMALL LETTER L#
			{125131, "8"},  // MA#* ( ???? �� 8 ) MENDE KIKAKUI DIGIT FIVE �� DIGIT EIGHT#
			{126464, "l"},  // MA# ( ???? �� l ) ARABIC MATHEMATICAL ALEF �� LATIN SMALL LETTER L# ��???����1��
			{126500, "o"},  // MA# ( ???? �� o ) ARABIC MATHEMATICAL INITIAL HEH �� LATIN SMALL LETTER O# ��???��
			{126564, "o"},  // MA# ( ???? �� o ) ARABIC MATHEMATICAL STRETCHED HEH �� LATIN SMALL LETTER O# ��???��
			{126592, "l"},  // MA# ( ???? �� l ) ARABIC MATHEMATICAL LOOPED ALEF �� LATIN SMALL LETTER L# ��???����1��
			{126596, "o"},  // MA# ( ???? �� o ) ARABIC MATHEMATICAL LOOPED HEH �� LATIN SMALL LETTER O# ��???��
			{127232, "O."}, // MA#* ( ?? �� O. ) DIGIT ZERO FULL STOP �� LATIN CAPITAL LETTER O, FULL STOP# ��0.��
			{127233, "O,"}, // MA#* ( ?? �� O, ) DIGIT ZERO COMMA �� LATIN CAPITAL LETTER O, COMMA# ��0,��
			{127234, "l,"}, // MA#* ( ?? �� l, ) DIGIT ONE COMMA �� LATIN SMALL LETTER L, COMMA# ��1,��
			{127235, "2,"}, // MA#* ( ?? �� 2, ) DIGIT TWO COMMA �� DIGIT TWO, COMMA#
			{127236, "3,"}, // MA#* ( ?? �� 3, ) DIGIT THREE COMMA �� DIGIT THREE, COMMA#
			{127237, "4,"}, // MA#* ( ?? �� 4, ) DIGIT FOUR COMMA �� DIGIT FOUR, COMMA#
			{127238, "5,"}, // MA#* ( ?? �� 5, ) DIGIT FIVE COMMA �� DIGIT FIVE, COMMA#
			{127239, "6,"}, // MA#* ( ?? �� 6, ) DIGIT SIX COMMA �� DIGIT SIX, COMMA#
			{127240, "7,"}, // MA#* ( ?? �� 7, ) DIGIT SEVEN COMMA �� DIGIT SEVEN, COMMA#
			{127241, "8,"}, // MA#* ( ?? �� 8, ) DIGIT EIGHT COMMA �� DIGIT EIGHT, COMMA#
			{127242, "9,"}, // MA#* ( ?? �� 9, ) DIGIT NINE COMMA �� DIGIT NINE, COMMA#
			{127248, "(A)"},// MA#* ( ?? �� (A) ) PARENTHESIZED LATIN CAPITAL LETTER A �� LEFT PARENTHESIS, LATIN CAPITAL LETTER A, RIGHT PARENTHESIS#
			{127249, "(B)"},// MA#* ( ?? �� (B) ) PARENTHESIZED LATIN CAPITAL LETTER B �� LEFT PARENTHESIS, LATIN CAPITAL LETTER B, RIGHT PARENTHESIS#
			{127250, "(C)"},// MA#* ( ?? �� (C) ) PARENTHESIZED LATIN CAPITAL LETTER C �� LEFT PARENTHESIS, LATIN CAPITAL LETTER C, RIGHT PARENTHESIS#
			{127251, "(D)"},// MA#* ( ?? �� (D) ) PARENTHESIZED LATIN CAPITAL LETTER D �� LEFT PARENTHESIS, LATIN CAPITAL LETTER D, RIGHT PARENTHESIS#
			{127252, "(E)"},// MA#* ( ?? �� (E) ) PARENTHESIZED LATIN CAPITAL LETTER E �� LEFT PARENTHESIS, LATIN CAPITAL LETTER E, RIGHT PARENTHESIS#
			{127253, "(F)"},// MA#* ( ?? �� (F) ) PARENTHESIZED LATIN CAPITAL LETTER F �� LEFT PARENTHESIS, LATIN CAPITAL LETTER F, RIGHT PARENTHESIS#
			{127254, "(G)"},// MA#* ( ?? �� (G) ) PARENTHESIZED LATIN CAPITAL LETTER G �� LEFT PARENTHESIS, LATIN CAPITAL LETTER G, RIGHT PARENTHESIS#
			{127255, "(H)"},// MA#* ( ?? �� (H) ) PARENTHESIZED LATIN CAPITAL LETTER H �� LEFT PARENTHESIS, LATIN CAPITAL LETTER H, RIGHT PARENTHESIS#
			{127256, "(l)"},// MA#* ( ?? �� (l) ) PARENTHESIZED LATIN CAPITAL LETTER I �� LEFT PARENTHESIS, LATIN SMALL LETTER L, RIGHT PARENTHESIS# ��(I)��
			{127257, "(J)"},// MA#* ( ?? �� (J) ) PARENTHESIZED LATIN CAPITAL LETTER J �� LEFT PARENTHESIS, LATIN CAPITAL LETTER J, RIGHT PARENTHESIS#
			{127258, "(K)"},// MA#* ( ?? �� (K) ) PARENTHESIZED LATIN CAPITAL LETTER K �� LEFT PARENTHESIS, LATIN CAPITAL LETTER K, RIGHT PARENTHESIS#
			{127259, "(L)"},// MA#* ( ?? �� (L) ) PARENTHESIZED LATIN CAPITAL LETTER L �� LEFT PARENTHESIS, LATIN CAPITAL LETTER L, RIGHT PARENTHESIS#
			{127260, "(M)"},// MA#* ( ?? �� (M) ) PARENTHESIZED LATIN CAPITAL LETTER M �� LEFT PARENTHESIS, LATIN CAPITAL LETTER M, RIGHT PARENTHESIS#
			{127261, "(N)"},// MA#* ( ?? �� (N) ) PARENTHESIZED LATIN CAPITAL LETTER N �� LEFT PARENTHESIS, LATIN CAPITAL LETTER N, RIGHT PARENTHESIS#
			{127262, "(O)"},// MA#* ( ?? �� (O) ) PARENTHESIZED LATIN CAPITAL LETTER O �� LEFT PARENTHESIS, LATIN CAPITAL LETTER O, RIGHT PARENTHESIS#
			{127263, "(P)"},// MA#* ( ?? �� (P) ) PARENTHESIZED LATIN CAPITAL LETTER P �� LEFT PARENTHESIS, LATIN CAPITAL LETTER P, RIGHT PARENTHESIS#
			{127264, "(Q)"},// MA#* ( ?? �� (Q) ) PARENTHESIZED LATIN CAPITAL LETTER Q �� LEFT PARENTHESIS, LATIN CAPITAL LETTER Q, RIGHT PARENTHESIS#
			{127265, "(R)"},// MA#* ( ?? �� (R) ) PARENTHESIZED LATIN CAPITAL LETTER R �� LEFT PARENTHESIS, LATIN CAPITAL LETTER R, RIGHT PARENTHESIS#
			{127266, "(S)"},// MA#* ( ?? �� (S) ) PARENTHESIZED LATIN CAPITAL LETTER S �� LEFT PARENTHESIS, LATIN CAPITAL LETTER S, RIGHT PARENTHESIS#
			{127267, "(T)"},// MA#* ( ?? �� (T) ) PARENTHESIZED LATIN CAPITAL LETTER T �� LEFT PARENTHESIS, LATIN CAPITAL LETTER T, RIGHT PARENTHESIS#
			{127268, "(U)"},// MA#* ( ?? �� (U) ) PARENTHESIZED LATIN CAPITAL LETTER U �� LEFT PARENTHESIS, LATIN CAPITAL LETTER U, RIGHT PARENTHESIS#
			{127269, "(V)"},// MA#* ( ?? �� (V) ) PARENTHESIZED LATIN CAPITAL LETTER V �� LEFT PARENTHESIS, LATIN CAPITAL LETTER V, RIGHT PARENTHESIS#
			{127270, "(W)"},// MA#* ( ?? �� (W) ) PARENTHESIZED LATIN CAPITAL LETTER W �� LEFT PARENTHESIS, LATIN CAPITAL LETTER W, RIGHT PARENTHESIS#
			{127271, "(X)"},// MA#* ( ?? �� (X) ) PARENTHESIZED LATIN CAPITAL LETTER X �� LEFT PARENTHESIS, LATIN CAPITAL LETTER X, RIGHT PARENTHESIS#
			{127272, "(Y)"},// MA#* ( ?? �� (Y) ) PARENTHESIZED LATIN CAPITAL LETTER Y �� LEFT PARENTHESIS, LATIN CAPITAL LETTER Y, RIGHT PARENTHESIS#
			{127273, "(Z)"},// MA#* ( ?? �� (Z) ) PARENTHESIZED LATIN CAPITAL LETTER Z �� LEFT PARENTHESIS, LATIN CAPITAL LETTER Z, RIGHT PARENTHESIS#
			{127274, "(S)"},// MA#* ( ?? �� (S) ) TORTOISE SHELL BRACKETED LATIN CAPITAL LETTER S �� LEFT PARENTHESIS, LATIN CAPITAL LETTER S, RIGHT PARENTHESIS# ����S����
			{128768, "QE"}, // MA#* ( ?? �� QE ) ALCHEMICAL SYMBOL FOR QUINTESSENCE �� LATIN CAPITAL LETTER Q, LATIN CAPITAL LETTER E#
			{128775, "AR"}, // MA#* ( ?? �� AR ) ALCHEMICAL SYMBOL FOR AQUA REGIA-2 �� LATIN CAPITAL LETTER A, LATIN CAPITAL LETTER R#
			{128844, "C"},  // MA#* ( ?? �� C ) ALCHEMICAL SYMBOL FOR CALX �� LATIN CAPITAL LETTER C#
			{128860, "sss"},// MA#* ( ?? �� sss ) ALCHEMICAL SYMBOL FOR STRATUM SUPER STRATUM �� LATIN SMALL LETTER S, LATIN SMALL LETTER S, LATIN SMALL LETTER S#
			{128872, "T"},  // MA#* ( ?? �� T ) ALCHEMICAL SYMBOL FOR CRUCIBLE-4 �� LATIN CAPITAL LETTER T#
			{128875, "MB"}, // MA#* ( ?? �� MB ) ALCHEMICAL SYMBOL FOR BATH OF MARY �� LATIN CAPITAL LETTER M, LATIN CAPITAL LETTER B#
			{128876, "VB"}, // MA#* ( ?? �� VB ) ALCHEMICAL SYMBOL FOR BATH OF VAPOURS �� LATIN CAPITAL LETTER V, LATIN CAPITAL LETTER B#
	};
}

namespace gal
{
	constexpr const char* find_confusable(const std::uint32_t codepoint)
	{
		const auto it = std::ranges::lower_bound(g_confusable, codepoint, std::ranges::less{}, [](const auto& confusable)
												 { return confusable.codepoint; });

		return it != std::ranges::end(g_confusable) && it->codepoint == codepoint ? it->text : nullptr;
	}
}
