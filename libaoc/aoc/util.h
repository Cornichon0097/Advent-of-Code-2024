#ifndef AOC_UTIL_H
#define AOC_UTIL_H

/**
 * \brief      Determines the input stream.
 *
 * \param[in]  argc  The count of arguments
 * \param[in]  argv  The arguments array
 *
 * \return     The input stream.
 */
FILE *input_stream(int argc, const char *const argv[]);

/**
 * \brief      Counts number of lines.
 *
 * \param      stream  The stream
 *
 * \return     The number of lines of stream.
 */
int lines_count(FILE* stream);

/**
 * \brief      Return lines size.
 *
 * \param      stream  The stream
 *
 * \return     The lines size of stream.
 */
int lines_size(FILE* stream);

#endif /* aoc/util.h */
