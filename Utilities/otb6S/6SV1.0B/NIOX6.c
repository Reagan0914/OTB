/* NIOX6.f -- translated by f2c (version 19970805).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#ifdef __cplusplus
extern "C" {
#endif
/* OTB patches: replace "f2c.h" by "otb_6S.h" */
/*#include "f2c.h"*/
#include "otb_6S.h"

/*<       subroutine    niox6(a,inu) >*/
/* Subroutine */ int niox6_(doublereal *a, integer *inu)
{
    /* Initialized data */

    static doublereal acr[2048]	/* was [8][256] */ = { 0.,0.,0.,0.,0.,0.,
	    15300.,15310.,0.,0.,0.,0.,0.,0.,15310.,15320.,0.,0.,0.,0.,0.,0.,
	    15320.,15330.,0.,0.,0.,0.,0.,0.,15330.,15340.,0.,0.,0.,0.,0.,0.,
	    15340.,15350.,0.,0.,0.,0.,0.,0.,15350.,15360.,0.,0.,0.,0.,0.,0.,
	    15360.,15370.,0.,0.,0.,0.,0.,0.,15370.,15380.,0.,0.,0.,0.,0.,0.,
	    15380.,15390.,0.,0.,0.,0.,0.,0.,15390.,15400.,0.,0.,0.,0.,0.,0.,
	    15400.,15410.,0.,0.,0.,0.,0.,0.,15410.,15420.,0.,0.,0.,0.,0.,0.,
	    15420.,15430.,0.,0.,0.,0.,0.,0.,15430.,15440.,0.,0.,0.,0.,0.,0.,
	    15440.,15450.,0.,0.,0.,0.,0.,0.,15450.,15460.,0.,0.,0.,0.,0.,0.,
	    15460.,15470.,0.,0.,0.,0.,0.,0.,15470.,15480.,0.,0.,0.,0.,0.,0.,
	    15480.,15490.,0.,0.,0.,0.,0.,0.,15490.,15500.,0.,0.,0.,0.,0.,0.,
	    15500.,15510.,0.,0.,0.,0.,0.,0.,15510.,15520.,0.,0.,0.,0.,0.,0.,
	    15520.,15530.,0.,0.,0.,0.,0.,0.,15530.,15540.,0.,0.,0.,0.,0.,0.,
	    15540.,15550.,0.,0.,0.,0.,0.,0.,15550.,15560.,0.,0.,0.,0.,0.,0.,
	    15560.,15570.,0.,0.,0.,0.,0.,0.,15570.,15580.,0.,0.,0.,0.,0.,0.,
	    15580.,15590.,0.,0.,0.,0.,0.,0.,15590.,15600.,0.,0.,0.,0.,0.,0.,
	    15600.,15610.,0.,0.,0.,0.,0.,0.,15610.,15620.,0.,0.,0.,0.,0.,0.,
	    15620.,15630.,0.,0.,0.,0.,0.,0.,15630.,15640.,0.,0.,0.,0.,0.,0.,
	    15640.,15650.,0.,0.,0.,0.,0.,0.,15650.,15660.,0.,0.,0.,0.,0.,0.,
	    15660.,15670.,0.,0.,0.,0.,0.,0.,15670.,15680.,0.,0.,0.,0.,0.,0.,
	    15680.,15690.,0.,0.,0.,0.,0.,0.,15690.,15700.,0.,0.,0.,0.,0.,0.,
	    15700.,15710.,0.,0.,0.,0.,0.,0.,15710.,15720.,0.,0.,0.,0.,0.,0.,
	    15720.,15730.,0.,0.,0.,0.,0.,0.,15730.,15740.,0.,0.,0.,0.,0.,0.,
	    15740.,15750.,0.,0.,0.,0.,0.,0.,15750.,15760.,0.,0.,0.,0.,0.,0.,
	    15760.,15770.,0.,0.,0.,0.,0.,0.,15770.,15780.,0.,0.,0.,0.,0.,0.,
	    15780.,15790.,0.,0.,0.,0.,0.,0.,15790.,15800.,0.,0.,0.,0.,0.,0.,
	    15800.,15810.,0.,0.,0.,0.,0.,0.,15810.,15820.,0.,0.,0.,0.,0.,0.,
	    15820.,15830.,0.,0.,0.,0.,0.,0.,15830.,15840.,0.,0.,0.,0.,0.,0.,
	    15840.,15850.,0.,0.,0.,0.,0.,0.,15850.,15860.,0.,0.,0.,0.,0.,0.,
	    15860.,15870.,0.,0.,0.,0.,0.,0.,15870.,15880.,0.,0.,0.,0.,0.,0.,
	    15880.,15890.,0.,0.,0.,0.,0.,0.,15890.,15900.,0.,0.,0.,0.,0.,0.,
	    15900.,15910.,0.,0.,0.,0.,0.,0.,15910.,15920.,0.,0.,0.,0.,0.,0.,
	    15920.,15930.,0.,0.,0.,0.,0.,0.,15930.,15940.,0.,0.,0.,0.,0.,0.,
	    15940.,15950.,0.,0.,0.,0.,0.,0.,15950.,15960.,0.,0.,0.,0.,0.,0.,
	    15960.,15970.,0.,0.,0.,0.,0.,0.,15970.,15980.,0.,0.,0.,0.,0.,0.,
	    15980.,15990.,0.,0.,0.,0.,0.,0.,15990.,1.6e4,0.,0.,0.,0.,0.,0.,
	    1.6e4,16010.,0.,0.,0.,0.,0.,0.,16010.,16020.,0.,0.,0.,0.,0.,0.,
	    16020.,16030.,0.,0.,0.,0.,0.,0.,16030.,16040.,0.,0.,0.,0.,0.,0.,
	    16040.,16050.,0.,0.,0.,0.,0.,0.,16050.,16060.,0.,0.,0.,0.,0.,0.,
	    16060.,16070.,0.,0.,0.,0.,0.,0.,16070.,16080.,0.,0.,0.,0.,0.,0.,
	    16080.,16090.,0.,0.,0.,0.,0.,0.,16090.,16100.,0.,0.,0.,0.,0.,0.,
	    16100.,16110.,0.,0.,0.,0.,0.,0.,16110.,16120.,0.,0.,0.,0.,0.,0.,
	    16120.,16130.,0.,0.,0.,0.,0.,0.,16130.,16140.,0.,0.,0.,0.,0.,0.,
	    16140.,16150.,0.,0.,0.,0.,0.,0.,16150.,16160.,0.,0.,0.,0.,0.,0.,
	    16160.,16170.,0.,0.,0.,0.,0.,0.,16170.,16180.,0.,0.,0.,0.,0.,0.,
	    16180.,16190.,0.,0.,0.,0.,0.,0.,16190.,16200.,0.,0.,0.,0.,0.,0.,
	    16200.,16210.,0.,0.,0.,0.,0.,0.,16210.,16220.,0.,0.,0.,0.,0.,0.,
	    16220.,16230.,0.,0.,0.,0.,0.,0.,16230.,16240.,0.,0.,0.,0.,0.,0.,
	    16240.,16250.,0.,0.,0.,0.,0.,0.,16250.,16260.,0.,0.,0.,0.,0.,0.,
	    16260.,16270.,0.,0.,0.,0.,0.,0.,16270.,16280.,0.,0.,0.,0.,0.,0.,
	    16280.,16290.,0.,0.,0.,0.,0.,0.,16290.,16300.,0.,0.,0.,0.,0.,0.,
	    16300.,16310.,0.,0.,0.,0.,0.,0.,16310.,16320.,0.,0.,0.,0.,0.,0.,
	    16320.,16330.,0.,0.,0.,0.,0.,0.,16330.,16340.,0.,0.,0.,0.,0.,0.,
	    16340.,16350.,0.,0.,0.,0.,0.,0.,16350.,16360.,0.,0.,0.,0.,0.,0.,
	    16360.,16370.,0.,0.,0.,0.,0.,0.,16370.,16380.,0.,0.,0.,0.,0.,0.,
	    16380.,16390.,0.,0.,0.,0.,0.,0.,16390.,16400.,0.,0.,0.,0.,0.,0.,
	    16400.,16410.,0.,0.,0.,0.,0.,0.,16410.,16420.,0.,0.,0.,0.,0.,0.,
	    16420.,16430.,0.,0.,0.,0.,0.,0.,16430.,16440.,0.,0.,0.,0.,0.,0.,
	    16440.,16450.,0.,0.,0.,0.,0.,0.,16450.,16460.,0.,0.,0.,0.,0.,0.,
	    16460.,16470.,0.,0.,0.,0.,0.,0.,16470.,16480.,0.,0.,0.,0.,0.,0.,
	    16480.,16490.,0.,0.,0.,0.,0.,0.,16490.,16500.,0.,0.,0.,0.,0.,0.,
	    16500.,16510.,0.,0.,0.,0.,0.,0.,16510.,16520.,0.,0.,0.,0.,0.,0.,
	    16520.,16530.,0.,0.,0.,0.,0.,0.,16530.,16540.,0.,0.,0.,0.,0.,0.,
	    16540.,16550.,0.,0.,0.,0.,0.,0.,16550.,16560.,0.,0.,0.,0.,0.,0.,
	    16560.,16570.,0.,0.,0.,0.,0.,0.,16570.,16580.,0.,0.,0.,0.,0.,0.,
	    16580.,16590.,0.,0.,0.,0.,0.,0.,16590.,16600.,0.,0.,0.,0.,0.,0.,
	    16600.,16610.,0.,0.,0.,0.,0.,0.,16610.,16620.,0.,0.,0.,0.,0.,0.,
	    16620.,16630.,0.,0.,0.,0.,0.,0.,16630.,16640.,0.,0.,0.,0.,0.,0.,
	    16640.,16650.,0.,0.,0.,0.,0.,0.,16650.,16660.,0.,0.,0.,0.,0.,0.,
	    16660.,16670.,0.,0.,0.,0.,0.,0.,16670.,16680.,0.,0.,0.,0.,0.,0.,
	    16680.,16690.,0.,0.,0.,0.,0.,0.,16690.,16700.,0.,0.,0.,0.,0.,0.,
	    16700.,16710.,0.,0.,0.,0.,0.,0.,16710.,16720.,0.,0.,0.,0.,0.,0.,
	    16720.,16730.,0.,0.,0.,0.,0.,0.,16730.,16740.,0.,0.,0.,0.,0.,0.,
	    16740.,16750.,0.,0.,0.,0.,0.,0.,16750.,16760.,0.,0.,0.,0.,0.,0.,
	    16760.,16770.,0.,0.,0.,0.,0.,0.,16770.,16780.,0.,0.,0.,0.,0.,0.,
	    16780.,16790.,0.,0.,0.,0.,0.,0.,16790.,16800.,0.,0.,0.,0.,0.,0.,
	    16800.,16810.,0.,0.,0.,0.,0.,0.,16810.,16820.,0.,0.,0.,0.,0.,0.,
	    16820.,16830.,0.,0.,0.,0.,0.,0.,16830.,16840.,0.,0.,0.,0.,0.,0.,
	    16840.,16850.,0.,0.,0.,0.,0.,0.,16850.,16860.,0.,0.,0.,0.,0.,0.,
	    16860.,16870.,0.,0.,0.,0.,0.,0.,16870.,16880.,0.,0.,0.,0.,0.,0.,
	    16880.,16890.,0.,0.,0.,0.,0.,0.,16890.,16900.,0.,0.,0.,0.,0.,0.,
	    16900.,16910.,0.,0.,0.,0.,0.,0.,16910.,16920.,0.,0.,0.,0.,0.,0.,
	    16920.,16930.,0.,0.,0.,0.,0.,0.,16930.,16940.,0.,0.,0.,0.,0.,0.,
	    16940.,16950.,0.,0.,0.,0.,0.,0.,16950.,16960.,0.,0.,0.,0.,0.,0.,
	    16960.,16970.,0.,0.,0.,0.,0.,0.,16970.,16980.,0.,0.,0.,0.,0.,0.,
	    16980.,16990.,0.,0.,0.,0.,0.,0.,16990.,1.7e4,0.,0.,0.,0.,0.,0.,
	    1.7e4,17010.,0.,0.,0.,0.,0.,0.,17010.,17020.,0.,0.,0.,0.,0.,0.,
	    17020.,17030.,0.,0.,0.,0.,0.,0.,17030.,17040.,0.,0.,0.,0.,0.,0.,
	    17040.,17050.,0.,0.,0.,0.,0.,0.,17050.,17060.,0.,0.,0.,0.,0.,0.,
	    17060.,17070.,0.,0.,0.,0.,0.,0.,17070.,17080.,0.,0.,0.,0.,0.,0.,
	    17080.,17090.,0.,0.,0.,0.,0.,0.,17090.,17100.,0.,0.,0.,0.,0.,0.,
	    17100.,17110.,0.,0.,0.,0.,0.,0.,17110.,17120.,0.,0.,0.,0.,0.,0.,
	    17120.,17130.,0.,0.,0.,0.,0.,0.,17130.,17140.,0.,0.,0.,0.,0.,0.,
	    17140.,17150.,0.,0.,0.,0.,0.,0.,17150.,17160.,0.,0.,0.,0.,0.,0.,
	    17160.,17170.,0.,0.,0.,0.,0.,0.,17170.,17180.,0.,0.,0.,0.,0.,0.,
	    17180.,17190.,0.,0.,0.,0.,0.,0.,17190.,17200.,0.,0.,0.,0.,0.,0.,
	    17200.,17210.,0.,0.,0.,0.,0.,0.,17210.,17220.,0.,0.,0.,0.,0.,0.,
	    17220.,17230.,0.,0.,0.,0.,0.,0.,17230.,17240.,0.,0.,0.,0.,0.,0.,
	    17240.,17250.,0.,0.,0.,0.,0.,0.,17250.,17260.,0.,0.,0.,0.,0.,0.,
	    17260.,17270.,0.,0.,0.,0.,0.,0.,17270.,17280.,0.,0.,0.,0.,0.,0.,
	    17280.,17290.,0.,0.,0.,0.,0.,0.,17290.,17300.,0.,0.,0.,0.,0.,0.,
	    17300.,17310.,0.,0.,0.,0.,0.,0.,17310.,17320.,0.,0.,0.,0.,0.,0.,
	    17320.,17330.,0.,0.,0.,0.,0.,0.,17330.,17340.,0.,0.,0.,0.,0.,0.,
	    17340.,17350.,0.,0.,0.,0.,0.,0.,17350.,17360.,0.,0.,0.,0.,0.,0.,
	    17360.,17370.,0.,0.,0.,0.,0.,0.,17370.,17380.,0.,0.,0.,0.,0.,0.,
	    17380.,17390.,0.,0.,0.,0.,0.,0.,17390.,17400.,0.,0.,0.,0.,0.,0.,
	    17400.,17410.,0.,0.,0.,0.,0.,0.,17410.,17420.,0.,0.,0.,0.,0.,0.,
	    17420.,17430.,0.,0.,0.,0.,0.,0.,17430.,17440.,0.,0.,0.,0.,0.,0.,
	    17440.,17450.,0.,0.,0.,0.,0.,0.,17450.,17460.,0.,0.,0.,0.,0.,0.,
	    17460.,17470.,0.,0.,0.,0.,0.,0.,17470.,17480.,0.,0.,0.,0.,0.,0.,
	    17480.,17490.,0.,0.,0.,0.,0.,0.,17490.,17500.,0.,0.,0.,0.,0.,0.,
	    17500.,17510.,0.,0.,0.,0.,0.,0.,17510.,17520.,0.,0.,0.,0.,0.,0.,
	    17520.,17530.,0.,0.,0.,0.,0.,0.,17530.,17540.,0.,0.,0.,0.,0.,0.,
	    17540.,17550.,0.,0.,0.,0.,0.,0.,17550.,17560.,0.,0.,0.,0.,0.,0.,
	    17560.,17570.,0.,0.,0.,0.,0.,0.,17570.,17580.,0.,0.,0.,0.,0.,0.,
	    17580.,17590.,0.,0.,0.,0.,0.,0.,17590.,17600.,0.,0.,0.,0.,0.,0.,
	    17600.,17610.,0.,0.,0.,0.,0.,0.,17610.,17620.,0.,0.,0.,0.,0.,0.,
	    17620.,17630.,0.,0.,0.,0.,0.,0.,17630.,17640.,0.,0.,0.,0.,0.,0.,
	    17640.,17650.,0.,0.,0.,0.,0.,0.,17650.,17660.,0.,0.,0.,0.,0.,0.,
	    17660.,17670.,0.,0.,0.,0.,0.,0.,17670.,17680.,0.,0.,0.,0.,0.,0.,
	    17680.,17690.,0.,0.,0.,0.,0.,0.,17690.,17700.,0.,0.,0.,0.,0.,0.,
	    17700.,17710.,0.,0.,0.,0.,0.,0.,17710.,17720.,0.,0.,0.,0.,0.,0.,
	    17720.,17730.,0.,0.,0.,0.,0.,0.,17730.,17740.,0.,0.,0.,0.,0.,0.,
	    17740.,17750.,0.,0.,0.,0.,0.,0.,17750.,17760.,0.,0.,0.,0.,0.,0.,
	    17760.,17770.,0.,0.,0.,0.,0.,0.,17770.,17780.,0.,0.,0.,0.,0.,0.,
	    17780.,17790.,0.,0.,0.,0.,0.,0.,17790.,17800.,0.,0.,0.,0.,0.,0.,
	    17800.,17810.,0.,0.,0.,0.,0.,0.,17810.,17820.,0.,0.,0.,0.,0.,0.,
	    17820.,17830.,0.,0.,0.,0.,0.,0.,17830.,17840.,0.,0.,0.,0.,0.,0.,
	    17840.,17850.,0.,0.,0.,0.,0.,0.,17850.,17860. };

    integer i__;

/*<        real a(8) >*/
/*<        real acr(8,256) >*/
/*<        integer inu,j,k,i >*/
/*     nitrous oxide (15300 - 17870 cm-1) */

/*<    >*/
    /* Parameter adjustments */
    --a;

    /* Function Body */
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/
/*<    >*/

/*<       do i=1,8 >*/
    for (i__ = 1; i__ <= 8; ++i__) {
/*<       a(i)=acr(i,inu) >*/
	a[i__] = acr[i__ + (*inu << 3) - 9];
/*<       enddo >*/
    }

/*<       return >*/
    return 0;
/*<       end >*/
} /* niox6_ */

#ifdef __cplusplus
	}
#endif
