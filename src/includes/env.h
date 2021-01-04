/**
 * @file env.h
 *
 * @author Killax-D | Dylan DONNE
 *
 * @brief Environnements variables
 *
 * This file contains all declarations and function regarding Environnements
 *
 */


#define DEBUG 0 /**< Is the program in DEBUG mode ? */

/**
 * Customize the logger of Raylib
 * @param msgType The type of log (LOG_INFO, LOG_ERROR, LOG_WARNING, LOG_DEBUG)
 * @param text The text to send
 * @param args The args to format text
 */
void logger(int msgType, const char *text, va_list args);