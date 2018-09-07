/*
 * Debug.hpp
 *
 *  Created on: 26 nov 2013
 *      Author: ulf
 */

#ifndef DEBUG_HPP_
#define DEBUG_HPP_

extern	int	debug_flags;
extern	int	debug_xml;

#define	DBG_FLAG_COLOR			(1 << 0)
#define	DBG_FLAG_CONFIG			(1 << 1)
#define	DBG_FLAG_DATE			(1 << 2)
#define	DBG_FLAG_FRAME			(1 << 3)
#define	DBG_FLAG_HANDUNITS		(1 << 4)
#define	DBG_FLAG_INI			(1 << 5)
#define	DBG_FLAG_INIT			(1 << 6)
#define	DBG_FLAG_MALLOC			(1 << 7)
#define	DBG_FLAG_READSECTION	(1 << 8)
#define	DBG_FLAG_SENSOR			(1 << 9)
#define	DBG_FLAG_TEMP			(1 << 10)
#define	DBG_FLAG_THREAD			(1 << 11)
#define	DBG_FLAG_UART			(1 << 12)
#define	DBG_FLAG_UART_THREAD	(1 << 13)
#define	DBG_FLAG_UDP			(1 << 14)
#define	DBG_FLAG_XML			(1 << 15)
#define	DBG_FLAG_ALL			(0xFFFFFFFF)

#define	COLOR_WRITE			if(debug_flags & DBG_FLAG_COLOR)		DebugPort.WriteLine
#define	CONFIG_WRITE		if(debug_flags & DBG_FLAG_CONFIG)		DebugPort.WriteLine
#define	DATE_WRITE			if(debug_flags & DBG_FLAG_DATE)			DebugPort.WriteLine
#define	FRAME_WRITE			if(debug_flags & DBG_FLAG_FRAME)		DebugPort.WriteLine
#define	HANDUNITS_WRITE		if(debug_flags & DBG_FLAG_HANDUNITS)	DebugPort.WriteLine
#define	INI_WRITE			if(debug_flags & DBG_FLAG_INI)			DebugPort.WriteLine
#define	INIT_WRITE			if(debug_flags & DBG_FLAG_INIT)			DebugPort.WriteLine
#define	MALLOC_WRITE		if(debug_flags & DBG_FLAG_MALLOC)		DebugPort.WriteLine
#define	READSECTION_WRITE	if(debug_flags & DBG_FLAG_READSECTION)	DebugPort.WriteLine
#define	SENSOR_WRITE		if(debug_flags & DBG_FLAG_SENSOR)		DebugPort.WriteLine
#define	TEMP_WRITE			if(debug_flags & DBG_FLAG_TEMP)			DebugPort.WriteLine
#define	THREAD_WRITE		if(debug_flags & DBG_FLAG_THREAD)		DebugPort.WriteLine
#define	UART_WRITE			if(debug_flags & DBG_FLAG_UART)			DebugPort.WriteLine
#define	UART_THREAD_WRITE	if(debug_flags & DBG_FLAG_UART_THREAD)	DebugPort.WriteLine
#define	UDP_WRITE			if(debug_flags & DBG_FLAG_UDP)			DebugPort.WriteLine
#define	XML_WRITE			if(debug_flags & DBG_FLAG_XML)			DebugPort.WriteLine

#define	IF_COLOR_FLAG			if(debug_flags & DBG_FLAG_COLOR)
#define	IF_CONFIG_FLAG			if(debug_flags & DBG_FLAG_CONFIG)
#define	IF_DATE_FLAG			if(debug_flags & DBG_FLAG_DATE)
#define	IF_FRAME_FLAG			if(debug_flags & DBG_FLAG_FRAME)
#define	IF_HANDUNITS_FLAG		if(debug_flags & DBG_FLAG_HANDUNITS)
#define	IF_INI_FLAG				if(debug_flags & DBG_FLAG_INI)
#define	IF_INIT_FLAG			if(debug_flags & DBG_FLAG_INIT)
#define	IF_MALLOC_FLAG			if(debug_flags & DBG_FLAG_MALLOC)
#define	IF_READSECTION_FLAG		if(debug_flags & DBG_FLAG_READSECTION)
#define	IF_SENSOR_FLAG			if(debug_flags & DBG_FLAG_TEMP)
#define	IF_TEMP_FLAG			if(debug_flags & DBG_FLAG_TEMP)
#define	IF_THREAD_FLAG			if(debug_flags & DBG_FLAG_THREAD)
#define	IF_UART_FLAG			if(debug_flags & DBG_FLAG_UART)
#define	IF_UART_THREAD_FLAG		if(debug_flags & DBG_FLAG_UART_THREAD)
#define	IF_UDP_FLAG				if(debug_flags & DBG_FLAG_UDP)
#define	IF_XML_FLAG				if(debug_flags & DBG_FLAG_XML)

#define	Delete(x)	{				\
	IF_MALLOC_FLAG {				\
		cout << "deleting " << #x;	\
		if (x == NULL) {			\
			cout << " (NULL)";		\
		} else {					\
			cout << endl;			\
		}							\
	}								\
	if ((x) != NULL) delete	x;		\
	IF_MALLOC_FLAG {				\
		cout << " /Done" << endl;	\
	}								\
}

#endif /* DEBUG_HPP_ */
