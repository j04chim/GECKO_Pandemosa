/**
 * logger.*
 * @author Joachim Rey <joachim@meowf.fr>
 */

/**
 * @fn log
 * @brief Log a message in std::in.
 * @param level The log level of the message.
 * @param message The message to print.
 *
 * Display a message in std::in given a log level between 0 (lowset)
 * and 3 (highest).
 * The log level of the program is define at compile time with LOG_LEVEL (eg.
 * -DLOG_LEVEL=2).
 * 0 -> info
 * 1 -> warn
 * 2 -> error
 * 3 -> fatal
 */
void logger( int level, const char* message );