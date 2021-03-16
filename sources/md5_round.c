/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_round.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:34:44 by jnovotny          #+#    #+#             */
/*   Updated: 2021/03/16 20:52:57 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Includes ********************************************************************
*/

#include "ft_ssl_md5.h"
#include <assert.h>

#ifndef LOG
# define LOG 1
#endif

#define T(x) g_op[x].t
/*
** Variables  ******************************************************************
*/

static const t_md5_op	g_op[64] = {
	{{0, 1, 2, 3}, 0, 7, 0xd76aa478, ft_md5_f},
	{{3, 0, 1, 2}, 1, 12, 0xe8c7b756, ft_md5_f},
	{{2, 3, 0, 1}, 2, 17, 0x242070db, ft_md5_f},
	{{1, 2, 3, 0}, 3, 22, 0xc1bdceee, ft_md5_f},
	{{0, 1, 2, 3}, 4, 7, 0xf57c0faf, ft_md5_f},
	{{3, 0, 1, 2}, 5, 12, 0x4787c62a, ft_md5_f},
	{{2, 3, 0, 1}, 6, 17, 0xa8304613, ft_md5_f},
	{{1, 2, 3, 0}, 7, 22, 0xfd469501, ft_md5_f},
	{{0, 1, 2, 3}, 8, 7, 0x698098d8, ft_md5_f},
	{{3, 0, 1, 2}, 9, 12, 0x8b44f7af, ft_md5_f},
	{{2, 3, 0, 1}, 10, 17, 0xffff5bb1, ft_md5_f},
	{{1, 2, 3, 0}, 11, 22, 0x895cd7be, ft_md5_f},
	{{0, 1, 2, 3}, 12, 7, 0x6b901122, ft_md5_f},
	{{3, 0, 1, 2}, 13, 12, 0xfd987193, ft_md5_f},
	{{2, 3, 0, 1}, 14, 17, 0xa679438e, ft_md5_f},
	{{1, 2, 3, 0}, 15, 22, 0x49b40821, ft_md5_f},
	{{0, 1, 2, 3}, 1, 5, 0xf61e2562, ft_md5_g},
	{{3, 0, 1, 2}, 6, 9, 0xc040b340, ft_md5_g},
	{{2, 3, 0, 1}, 11, 14, 0x265e5a51, ft_md5_g},
	{{1, 2, 3, 0}, 0, 20, 0xe9b6c7aa, ft_md5_g},
	{{0, 1, 2, 3}, 5, 5, 0xd62f105d, ft_md5_g},
	{{3, 0, 1, 2}, 10, 9, 0x2441453, ft_md5_g},
	{{2, 3, 0, 1}, 15, 14, 0xd8a1e681, ft_md5_g},
	{{1, 2, 3, 0}, 4, 20, 0xe7d3fbc8, ft_md5_g},
	{{0, 1, 2, 3}, 9, 5, 0x21e1cde6, ft_md5_g},
	{{3, 0, 1, 2}, 14, 9, 0xc33707d6, ft_md5_g},
	{{2, 3, 0, 1}, 3, 14, 0xf4d50d87, ft_md5_g},
	{{1, 2, 3, 0}, 8, 20, 0x455a14ed, ft_md5_g},
	{{0, 1, 2, 3}, 13, 5, 0xa9e3e905, ft_md5_g},
	{{3, 0, 1, 2}, 2, 9, 0xfcefa3f8, ft_md5_g},
	{{2, 3, 0, 1}, 7, 14, 0x676f02d9, ft_md5_g},
	{{1, 2, 3, 0}, 12, 20, 0x8d2a4c8a, ft_md5_g},
	{{0, 1, 2, 3}, 5, 4, 0xfffa3942, ft_md5_h},
	{{3, 0, 1, 2}, 8, 11, 0x8771f681, ft_md5_h},
	{{2, 3, 0, 1}, 11, 16, 0x6d9d6122, ft_md5_h},
	{{1, 2, 3, 0}, 14, 23, 0xfde5380c, ft_md5_h},
	{{0, 1, 2, 3}, 1, 4, 0xa4beea44, ft_md5_h},
	{{3, 0, 1, 2}, 4, 11, 0x4bdecfa9, ft_md5_h},
	{{2, 3, 0, 1}, 7, 16, 0xf6bb4b60, ft_md5_h},
	{{1, 2, 3, 0}, 10, 23, 0xbebfbc70, ft_md5_h},
	{{0, 1, 2, 3}, 13, 4, 0x289b7ec6, ft_md5_h},
	{{3, 0, 1, 2}, 0, 11, 0xeaa127fa, ft_md5_h},
	{{2, 3, 0, 1}, 3, 16, 0xd4ef3085, ft_md5_h},
	{{1, 2, 3, 0}, 6, 23, 0x4881d05, ft_md5_h},
	{{0, 1, 2, 3}, 9, 4, 0xd9d4d039, ft_md5_h},
	{{3, 0, 1, 2}, 12, 11, 0xe6db99e5, ft_md5_h},
	{{2, 3, 0, 1}, 15, 16, 0x1fa27cf8, ft_md5_h},
	{{1, 2, 3, 0}, 2, 23, 0xc4ac5665, ft_md5_h},
	{{0, 1, 2, 3}, 0, 6, 0xf4292244, ft_md5_i},
	{{3, 0, 1, 2}, 7, 10, 0x432aff97, ft_md5_i},
	{{2, 3, 0, 1}, 14, 15, 0xab9423a7, ft_md5_i},
	{{1, 2, 3, 0}, 5, 21, 0xfc93a039, ft_md5_i},
	{{0, 1, 2, 3}, 12, 6, 0x655b59c3, ft_md5_i},
	{{3, 0, 1, 2}, 3, 10, 0x8f0ccc92, ft_md5_i},
	{{2, 3, 0, 1}, 10, 15, 0xffeff47d, ft_md5_i},
	{{1, 2, 3, 0}, 1, 21, 0x85845dd1, ft_md5_i},
	{{0, 1, 2, 3}, 8, 6, 0x6fa87e4f, ft_md5_i},
	{{3, 0, 1, 2}, 15, 10, 0xfe2ce6e0, ft_md5_i},
	{{2, 3, 0, 1}, 6, 15, 0xa3014314, ft_md5_i},
	{{1, 2, 3, 0}, 13, 21, 0x4e0811a1, ft_md5_i},
	{{0, 1, 2, 3}, 4, 6, 0xf7537e82, ft_md5_i},
	{{3, 0, 1, 2}, 11, 10, 0xbd3af235, ft_md5_i},
	{{2, 3, 0, 1}, 2, 15, 0x2ad7d2bb, ft_md5_i},
	{{1, 2, 3, 0}, 9, 21, 0xeb86d391, ft_md5_i}
};

/*
** Functions  ******************************************************************
*/

static void		unittest_op()
{
	assert(T(0)==3614090360);
	assert(T(1)==3905402710);
	assert(T(2)==606105819);
	assert(T(3)==3250441966);
	assert(T(4)==4118548399);
	assert(T(5)==1200080426);
	assert(T(6)==2821735955);
	assert(T(7)==4249261313);
	assert(T(8)==1770035416);
	assert(T(9)==2336552879);
	assert(T(10)==4294925233);
	assert(T(11)==2304563134);
	assert(T(12)==1804603682);
	assert(T(13)==4254626195);
	assert(T(14)==2792965006);
	assert(T(15)==1236535329);
	assert(T(16)==4129170786);
	assert(T(17)==3225465664);
	assert(T(18)==643717713);
	assert(T(19)==3921069994);
	assert(T(20)==3593408605);
	assert(T(21)==38016083);
	assert(T(22)==3634488961);
	assert(T(23)==3889429448);
	assert(T(24)==568446438);
	assert(T(25)==3275163606);
	assert(T(26)==4107603335);
	assert(T(27)==1163531501);
	assert(T(28)==2850285829);
	assert(T(29)==4243563512);
	assert(T(30)==1735328473);
	assert(T(31)==2368359562);
	assert(T(32)==4294588738);
	assert(T(33)==2272392833);
	assert(T(34)==1839030562);
	assert(T(35)==4259657740);
	assert(T(36)==2763975236);
	assert(T(37)==1272893353);
	assert(T(38)==4139469664);
	assert(T(39)==3200236656);
	assert(T(40)==681279174);
	assert(T(41)==3936430074);
	assert(T(42)==3572445317);
	assert(T(43)==76029189);
	assert(T(44)==3654602809);
	assert(T(45)==3873151461);
	assert(T(46)==530742520);
	assert(T(47)==3299628645);
	assert(T(48)==4096336452);
	assert(T(49)==1126891415);
	assert(T(50)==2878612391);
	assert(T(51)==4237533241);
	assert(T(52)==1700485571);
	assert(T(53)==2399980690);
	assert(T(54)==4293915773);
	assert(T(55)==2240044497);
	assert(T(56)==1873313359);
	assert(T(57)==4264355552);
	assert(T(58)==2734768916);
	assert(T(59)==1309151649);
	assert(T(60)==4149444226);
	assert(T(61)==3174756917);
	assert(T(62)==718787259);
	assert(T(63)==3951481745);

	assert(g_op[0].s==7);
	assert(g_op[1].s==12);
	assert(g_op[2].s==17);
	assert(g_op[3].s==22);
	assert(g_op[4].s==7);
	assert(g_op[5].s==12);
	assert(g_op[6].s==17);
	assert(g_op[7].s==22);
	assert(g_op[8].s==7);
	assert(g_op[9].s==12);
	assert(g_op[10].s==17);
	assert(g_op[11].s==22);
	assert(g_op[12].s==7);
	assert(g_op[13].s==12);
	assert(g_op[14].s==17);
	assert(g_op[15].s==22);
	assert(g_op[16].s==5);
	assert(g_op[17].s==9);
	assert(g_op[18].s==14);
	assert(g_op[19].s==20);
	assert(g_op[20].s==5);
	assert(g_op[21].s==9);
	assert(g_op[22].s==14);
	assert(g_op[23].s==20);
	assert(g_op[24].s==5);
	assert(g_op[25].s==9);
	assert(g_op[26].s==14);
	assert(g_op[27].s==20);
	assert(g_op[28].s==5);
	assert(g_op[29].s==9);
	assert(g_op[30].s==14);
	assert(g_op[31].s==20);
	assert(g_op[32].s==4);
	assert(g_op[33].s==11);
	assert(g_op[34].s==16);
	assert(g_op[35].s==23);
	assert(g_op[36].s==4);
	assert(g_op[37].s==11);
	assert(g_op[38].s==16);
	assert(g_op[39].s==23);
	assert(g_op[40].s==4);
	assert(g_op[41].s==11);
	assert(g_op[42].s==16);
	assert(g_op[43].s==23);
	assert(g_op[44].s==4);
	assert(g_op[45].s==11);
	assert(g_op[46].s==16);
	assert(g_op[47].s==23);
	assert(g_op[48].s==6);
	assert(g_op[49].s==10);
	assert(g_op[50].s==15);
	assert(g_op[51].s==21);
	assert(g_op[52].s==6);
	assert(g_op[53].s==10);
	assert(g_op[54].s==15);
	assert(g_op[55].s==21);
	assert(g_op[56].s==6);
	assert(g_op[57].s==10);
	assert(g_op[58].s==15);
	assert(g_op[59].s==21);
	assert(g_op[60].s==6);
	assert(g_op[61].s==10);
	assert(g_op[62].s==15);
	assert(g_op[63].s==21);
}

static void		a_test(t_md5_buffers *buf, uint8_t i)
{
	switch (i)
	{
		case 0:
			assert(buf->four[0] == 2774538228 && \
					buf->four[1] == 4023233417 && \
					buf->four[2] == 2562383102 && \
					buf->four[3] == 271733878);
			break;
		case 1:
			assert(buf->four[0] == 2774538228 && \
					buf->four[1] == 4023233417 && \
					buf->four[2] == 2562383102 && \
					buf->four[3] == 4074079073);
			break;
		case 2:
			assert(buf->four[0] == 2774538228 && \
					buf->four[1] == 4023233417 && \
					buf->four[2] == 3864549287 && \
					buf->four[3] == 4074079073);
			break;
		case 3:
			assert(buf->four[0] == 2774538228 && \
					buf->four[1] == 1618843270 && \
					buf->four[2] == 3864549287 && \
					buf->four[3] == 4074079073);
			break;
		case 4:
			assert(buf->four[0] == 983391180 && \
					buf->four[1] == 1618843270 && \
					buf->four[2] == 3864549287 && \
					buf->four[3] == 4074079073);
			break;
		case 5:
			assert(buf->four[0] == 983391180 && \
					buf->four[1] == 1618843270 && \
					buf->four[2] == 3864549287 && \
					buf->four[3] == 3768614327);
			break;
		case 6:
			assert(buf->four[0] == 983391180 && \
					buf->four[1] == 1618843270 && \
					buf->four[2] == 3541949571 && \
					buf->four[3] == 3768614327);
			break;
		case 7:
			assert(buf->four[0] == 983391180 && \
					buf->four[1] == 2830069157 && \
					buf->four[2] == 3541949571 && \
					buf->four[3] == 3768614327);
			break;
		case 8:
			assert(buf->four[0] == 3193440599 && \
					buf->four[1] == 2830069157 && \
					buf->four[2] == 3541949571 && \
					buf->four[3] == 3768614327);
			break;
		case 9:
			assert(buf->four[0] == 3193440599 && \
					buf->four[1] == 2830069157 && \
					buf->four[2] == 3541949571 && \
					buf->four[3] == 4085694118);
			break;
		case 10:
			assert(buf->four[0] == 3193440599 && \
					buf->four[1] == 2830069157 && \
					buf->four[2] == 4127054131 && \
					buf->four[3] == 4085694118);
			break;
		case 11:
			assert(buf->four[0] == 3193440599 && \
					buf->four[1] == 1749630314 && \
					buf->four[2] == 4127054131 && \
					buf->four[3] == 4085694118);
			break;
		case 12:
			assert(buf->four[0] == 1143229688 && \
					buf->four[1] == 1749630314 && \
					buf->four[2] == 4127054131 && \
					buf->four[3] == 4085694118);
			break;
		case 13:
			assert(buf->four[0] == 1143229688 && \
					buf->four[1] == 1749630314 && \
					buf->four[2] == 4127054131 && \
					buf->four[3] == 3506346791);
			break;
		case 14:
			assert(buf->four[0] == 1143229688 && \
					buf->four[1] == 1749630314 && \
					buf->four[2] == 1667277919 && \
					buf->four[3] == 3506346791);
			break;
		case 15:
			assert(buf->four[0] == 1143229688 && \
					buf->four[1] == 4028513506 && \
					buf->four[2] == 1667277919 && \
					buf->four[3] == 3506346791);
			break;
		case 16:
			assert(buf->four[0] == 2620659559 && \
					buf->four[1] == 4028513506 && \
					buf->four[2] == 1667277919 && \
					buf->four[3] == 3506346791);
			break;
		case 17:
			assert(buf->four[0] == 2620659559 && \
					buf->four[1] == 4028513506 && \
					buf->four[2] == 1667277919 && \
					buf->four[3] == 2534060969);
			break;
		case 18:
			assert(buf->four[0] == 2620659559 && \
					buf->four[1] == 4028513506 && \
					buf->four[2] == 3818913059 && \
					buf->four[3] == 2534060969);
			break;
		case 19:
			assert(buf->four[0] == 2620659559 && \
					buf->four[1] == 2368064614 && \
					buf->four[2] == 3818913059 && \
					buf->four[3] == 2534060969);
			break;
		case 20:
			assert(buf->four[0] == 2353285424 && \
					buf->four[1] == 2368064614 && \
					buf->four[2] == 3818913059 && \
					buf->four[3] == 2534060969);
			break;
		case 21:
			assert(buf->four[0] == 2353285424 && \
					buf->four[1] == 2368064614 && \
					buf->four[2] == 3818913059 && \
					buf->four[3] == 1919355258);
			break;
		case 22:
			assert(buf->four[0] == 2353285424 && \
					buf->four[1] == 2368064614 && \
					buf->four[2] == 766294179 && \
					buf->four[3] == 1919355258);
			break;
		case 23:
			assert(buf->four[0] == 2353285424 && \
					buf->four[1] == 926673584 && \
					buf->four[2] == 766294179 && \
					buf->four[3] == 1919355258);
			break;
		case 24:
			assert(buf->four[0] == 4051035053 && \
					buf->four[1] == 926673584 && \
					buf->four[2] == 766294179 && \
					buf->four[3] == 1919355258);
			break;
		case 25:
			assert(buf->four[0] == 4051035053 && \
					buf->four[1] == 926673584 && \
					buf->four[2] == 766294179 && \
					buf->four[3] == 2640180862);
			break;
		case 26:
			assert(buf->four[0] == 4051035053 && \
					buf->four[1] == 926673584 && \
					buf->four[2] == 2276979829 && \
					buf->four[3] == 2640180862);
			break;
		case 27:
			assert(buf->four[0] == 4051035053 && \
					buf->four[1] == 3371733428 && \
					buf->four[2] == 2276979829 && \
					buf->four[3] == 2640180862);
			break;
		case 28:
			assert(buf->four[0] == 2474913432 && \
					buf->four[1] == 3371733428 && \
					buf->four[2] == 2276979829 && \
					buf->four[3] == 2640180862);
			break;
		case 29:
			assert(buf->four[0] == 2474913432 && \
					buf->four[1] == 3371733428 && \
					buf->four[2] == 2276979829 && \
					buf->four[3] == 3338943332);
			break;
		case 30:
			assert(buf->four[0] == 2474913432 && \
					buf->four[1] == 3371733428 && \
					buf->four[2] == 2493705198 && \
					buf->four[3] == 3338943332);
			break;
		case 31:
			assert(buf->four[0] == 2474913432 && \
					buf->four[1] == 927307295 && \
					buf->four[2] == 2493705198 && \
					buf->four[3] == 3338943332);
			break;
		case 32:
			assert(buf->four[0] == 3177217310 && \
					buf->four[1] == 927307295 && \
					buf->four[2] == 2493705198 && \
					buf->four[3] == 3338943332);
			break;
		case 33:
			assert(buf->four[0] == 3177217310 && \
					buf->four[1] == 927307295 && \
					buf->four[2] == 2493705198 && \
					buf->four[3] == 2801213573);
			break;
		case 34:
			assert(buf->four[0] == 3177217310 && \
					buf->four[1] == 927307295 && \
					buf->four[2] == 3213578136 && \
					buf->four[3] == 2801213573);
			break;
		case 35:
			assert(buf->four[0] == 3177217310 && \
					buf->four[1] == 3673682696 && \
					buf->four[2] == 3213578136 && \
					buf->four[3] == 2801213573);
			break;
		case 36:
			assert(buf->four[0] == 900213370 && \
					buf->four[1] == 3673682696 && \
					buf->four[2] == 3213578136 && \
					buf->four[3] == 2801213573);
			break;
		case 37:
			assert(buf->four[0] == 900213370 && \
					buf->four[1] == 3673682696 && \
					buf->four[2] == 3213578136 && \
					buf->four[3] == 2313219223);
			break;
		case 38:
			assert(buf->four[0] == 900213370 && \
					buf->four[1] == 3673682696 && \
					buf->four[2] == 1522403740 && \
					buf->four[3] == 2313219223);
			break;
		case 39:
			assert(buf->four[0] == 900213370 && \
					buf->four[1] == 3481166043 && \
					buf->four[2] == 1522403740 && \
					buf->four[3] == 2313219223);
			break;
		case 40:
			assert(buf->four[0] == 1975603682 && \
					buf->four[1] == 3481166043 && \
					buf->four[2] == 1522403740 && \
					buf->four[3] == 2313219223);
			break;
		case 41:
			assert(buf->four[0] == 1975603682 && \
					buf->four[1] == 3481166043 && \
					buf->four[2] == 1522403740 && \
					buf->four[3] == 2486045830);
			break;
		case 42:
			assert(buf->four[0] == 1975603682 && \
					buf->four[1] == 3481166043 && \
					buf->four[2] == 202271428 && \
					buf->four[3] == 2486045830);
			break;
		case 43:
			assert(buf->four[0] == 1975603682 && \
					buf->four[1] == 3429850782 && \
					buf->four[2] == 202271428 && \
					buf->four[3] == 2486045830);
			break;
		case 44:
			assert(buf->four[0] == 180686360 && \
					buf->four[1] == 3429850782 && \
					buf->four[2] == 202271428 && \
					buf->four[3] == 2486045830);
			break;
		case 45:
			assert(buf->four[0] == 180686360 && \
					buf->four[1] == 3429850782 && \
					buf->four[2] == 202271428 && \
					buf->four[3] == 2043312197);
			break;
		case 46:
			assert(buf->four[0] == 180686360 && \
					buf->four[1] == 3429850782 && \
					buf->four[2] == 2320130902 && \
					buf->four[3] == 2043312197);
			break;
		case 47:
			assert(buf->four[0] == 180686360 && \
					buf->four[1] == 2442105787 && \
					buf->four[2] == 2320130902 && \
					buf->four[3] == 2043312197);
			break;
		case 48:
			assert(buf->four[0] == 3401121346 && \
					buf->four[1] == 2442105787 && \
					buf->four[2] == 2320130902 && \
					buf->four[3] == 2043312197);
			break;
		case 49:
			assert(buf->four[0] == 3401121346 && \
					buf->four[1] == 2442105787 && \
					buf->four[2] == 2320130902 && \
					buf->four[3] == 1783475950);
			break;
		case 50:
			assert(buf->four[0] == 3401121346 && \
					buf->four[1] == 2442105787 && \
					buf->four[2] == 908500031 && \
					buf->four[3] == 1783475950);
			break;
		case 51:
			assert(buf->four[0] == 3401121346 && \
					buf->four[1] == 518260203 && \
					buf->four[2] == 908500031 && \
					buf->four[3] == 1783475950);
			break;
		case 52:
			assert(buf->four[0] == 2553051233 && \
					buf->four[1] == 518260203 && \
					buf->four[2] == 908500031 && \
					buf->four[3] == 1783475950);
			break;
		case 53:
			assert(buf->four[0] == 2553051233 && \
					buf->four[1] == 518260203 && \
					buf->four[2] == 908500031 && \
					buf->four[3] == 1746051938);
			break;
		case 54:
			assert(buf->four[0] == 2553051233 && \
					buf->four[1] == 518260203 && \
					buf->four[2] == 1912370953 && \
					buf->four[3] == 1746051938);
			break;
		case 55:
			assert(buf->four[0] == 2553051233 && \
					buf->four[1] == 2301952448 && \
					buf->four[2] == 1912370953 && \
					buf->four[3] == 1746051938);
			break;
		case 56:
			assert(buf->four[0] == 4273824509 && \
					buf->four[1] == 2301952448 && \
					buf->four[2] == 1912370953 && \
					buf->four[3] == 1746051938);
			break;
		case 57:
			assert(buf->four[0] == 4273824509 && \
					buf->four[1] == 2301952448 && \
					buf->four[2] == 1912370953 && \
					buf->four[3] == 680749684);
			break;
		case 58:
			assert(buf->four[0] == 4273824509 && \
					buf->four[1] == 2301952448 && \
					buf->four[2] == 1407399206 && \
					buf->four[3] == 680749684);
			break;
		case 59:
			assert(buf->four[0] == 4273824509 && \
					buf->four[1] == 2857208547 && \
					buf->four[2] == 1407399206 && \
					buf->four[3] == 680749684);
			break;
		case 60:
			assert(buf->four[0] == 1378917899 && \
					buf->four[1] == 2857208547 && \
					buf->four[2] == 1407399206 && \
					buf->four[3] == 680749684);
			break;
		case 61:
			assert(buf->four[0] == 1378917899 && \
					buf->four[1] == 2857208547 && \
					buf->four[2] == 1407399206 && \
					buf->four[3] == 1358177011);
			break;
		case 62:
			assert(buf->four[0] == 1378917899 && \
					buf->four[1] == 2857208547 && \
					buf->four[2] == 1239344691 && \
					buf->four[3] == 1358177011);
			break;
		case 63:
			assert(buf->four[0] == 1378917899 && \
					buf->four[1] == 3102295607 && \
					buf->four[2] == 1239344691 && \
					buf->four[3] == 1358177011);
			break;
		default:
			ft_printf("WTF i=%u\n", i);
			break;
	}

}
static void		md5_do_op(
	t_md5_buffers *bufs,
	t_md5_block *block,
	const t_md5_op *op)
{
	uint32_t	tmp;

	bufs->four[op->o[0]] += op->fnc(bufs->four[op->o[1]],
									bufs->four[op->o[2]],
									bufs->four[op->o[3]]) +
							block->x[op->ix] +
							op->t;
	bufs->four[op->o[0]] = ft_uint32_left_circular_shift(\
								bufs->four[op->o[0]], \
								op->s);
	bufs->four[op->o[0]] += bufs->four[op->o[1]];
}

int				md5_block(t_md5_state *state)
{
	t_md5_buffers	buffers;
	uint8_t			i;
	char		*out;
	size_t		out_size;
	int			err;

	unittest_op();
	buffers.four[0] = state->bufs.four[0];
	buffers.four[1] = state->bufs.four[1];
	buffers.four[2] = state->bufs.four[2];
	buffers.four[3] = state->bufs.four[3];
	ft_printf("A=%u, B=%u, C=%u, D=%u\n", buffers.four[0], buffers.four[1], buffers.four[2], buffers.four[3]);
	ft_printf("Block:\n");
	for (int test=0; test < 16; test++)
	{
		ft_printf("[%d]%u\n",test, state->block.x[test]);
	}
	i = 0;
	while (i < 64)
	{
		md5_do_op(&buffers, &state->block, &g_op[i]);
		if (LOG)
		{
			ft_printf("%02u: A=%u, B=%u, C=%u, D=%u\n", i, buffers.four[0], buffers.four[1], buffers.four[2], buffers.four[3]);
			// out = NULL;
			// out_size = 0;
			// if ((err = ft_to_hexstr((uint8_t *)&buffers, MD5_OUT_SIZE, &out, &out_size)) != FT_SSL_OK)
			// 	return (err);
			// ft_printf("%02u: ", i);
			// ft_print_fmt_block(out);
			// free(out);
		}
		a_test(&buffers, i);
		i++;
	}
	state->bufs.four[0] += buffers.four[0];
	state->bufs.four[1] += buffers.four[1];
	state->bufs.four[2] += buffers.four[2];
	state->bufs.four[3] += buffers.four[3];
	return (FT_SSL_OK);
}
