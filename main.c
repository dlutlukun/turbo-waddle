#include <stdio.h>
#include <stdlib.h>

typedef signed char             int8_t;
typedef short int               int16_t;
typedef int                     int32_t;
typedef unsigned char           uint8_t;
typedef unsigned short int      uint16_t;
typedef unsigned int            uint32_t;

typedef	struct
{
	int16_t	    i2T;
	uint32_t	u4AD;
}T_TAB_TypeDef;

T_TAB_TypeDef	gcstNTCTab[] =
{
	{	-400,	400000000	},		/*	0	*/
	{	-350,	260000000	},		/*	1	*/
	{	-300,	190000000	},		/*	2	*/
	{	-250,	150000000   },		/*	3	*/
	{	-200,	110000000	},		/*	4	*/
	{	-150,	75000000	},		/*	5	*/
	{	-100,	56000000	},		/*	6	*/
	{	-50,	43000000	},		/*	7	*/
	{	0,		33000000	},		/*	8	*/
	{	50,		26000000    },		/*	9	*/
	{	100,	20000000	},		/*	10	*/
	{	150,	16000000	},		/*	11	*/
	{	200,	13000000	},		/*	12	*/
	{	250,	10000000	},		/*	13	*/
	{	300,	8200000 	},		/*	14	*/
	{	350,	6500000 	},		/*	15	*/
	{	400,	5400000		},		/*	16	*/
	{	450,	4300000		},		/*	17	*/
	{	500,	3600000		},		/*	18	*/
	{	550,	3000000		},		/*	19	*/
	{	600,	2500000		},		/*	20	*/
	{	650,	2000000		},		/*	21	*/
	{	700,	1800000	    },		/*	22	*/
	{	750,	1600000	    },		/*	23	*/
	{	800,	1300000	    },		/*	24	*/
	{	850,	1000000	    },		/*	25	*/
	{	900,	920000	    },		/*	26	*/
	{	950,	780000	    },		/*	27	*/
	{	1000,	650000	    },		/*	28	*/
	{	1050,	570000	    },		/*	29	*/
	{	1100,	490000	    },		/*	30	*/
	{	1150,	430000	    },		/*	31	*/
	{	1200,	380000	    },		/*	32	*/
};

int16_t round_F32toI16(float var)
{
	int16_t	retval = 0;

	if(var < ((float) 0.0))
	{
		var	=	(int16_t) (var - ((float) 0.5));
	}
	else
	{
		var	=	(int16_t) (var + ((float) 0.5));
	}

	return(retval);
}

int16_t	CalcT_NTC(void)
{
	uint8_t		i, index = 0;
	int16_t		i2_t = 0;
	int32_t		i4_r;
	float		f4_tmp;

	/*	i4_r单位为0.1ohm, 	gstuInfo.DRO.i4Liner_R[AD_AIN3]单位为 1mohm(0.001ohm)		*/
	i4_r	=	gstuInfo.DRO.i4Liner_R[AD_AIN3] / 100L;

	if(	(i4_r >= gcstNTCTab[0].i4R)
	||	(gstuInfo.DRO.u2ErrS & ERR_NTC_LINE_OPEN))			/*	-400du, 400Kohm	*/
	{
		i2_t	=	-400;
	}
	else if((i4_r <= gcstNTCTab[NTC_TAB_UNIT_NUM - 1].i4R)	/*	120du, 380ohm	*/
		||	(gstuInfo.DRO.u2ErrS & ERR_NTC_LINE_SHORT))
	{
		i2_t	=	1200;
	}
	else
	{
		for(i = 0; i < NTC_TAB_UNIT_NUM - 1; i += 1)
		{
			if((i4_r <= gcstNTCTab[i].i4R) && (i4_r > gcstNTCTab[i + 1].i4R))
			{
				index	=	i;
				break;
			}
		}

		f4_tmp	=	( ((float) (i4_r - gcstNTCTab[index].i4R))
				/	  ((float) (gcstNTCTab[index + 1].i4R - gcstNTCTab[index].i4R)) )
				*	  ((float) (gcstNTCTab[index + 1].i2T - gcstNTCTab[index].i2T))
				+	  ((float) gcstNTCTab[index].i2T);
		i2_t	=	round_F32toI16(f4_tmp);
	}

	return(i2_t);
}



/* TEST CODE */
int main()
{
    int16_t     i = 0;
    uint32_t    u = 0;

        /* test input 350000m~1000000m  */
//    for(u = 350000;u <= 1000000;u += 10000)
//    {
//        i = Conversion(u);
//        printf("%d\n",i);
//    }

        /* input 1000000~20000000       */
//    for(u = 1000000; u <= 20000000; u += 100000)
//    {
//        i = Conversion(u);
//        printf("%d\n",i);
//    }
        /* input 20000000~ 405000000    */
      for(u = 20000000; u <= 405000000; u += 1000000)
      {
          i = Conversion(u);
          printf("%d\n",i);
      }
    return 0;
}



