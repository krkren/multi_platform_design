/**
 * About newly added internal (partially plugin-public) functions and classes
 */

/**
 * Converts RGBA to BGRA (or vice versa) for dest with a width of len.
 * Due to the nature of the conversion, the same process can be used for converting BRGA to RGBA.
 * The process only swaps red and blue, leaving the others as they are.
 */
void TVPRedBlueSwap(tjs_uint32 *dest, tjs_int len);


/**
 * Copies src, converted from RGBA to BGRA (or vice versa), to dest with a width of len.
 * Due to the nature of the conversion, the same process can be used for converting BRGA to RGBA.
 * The process only swaps red and blue, leaving the others as they are.
 */
void TVPRedBlueSwapCopy(tjs_uint8 *dest, const tjs_uint8 *src, tjs_int len);
