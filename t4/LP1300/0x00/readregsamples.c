#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/user.h>
#include "syscalls.h"

/**
 * read_str_from_reg - Retrieves string from memory address stored in a register
 * @buffer: char buffer to write string to
 * @pid: Process ID for PTRACE_PEEKDATA request
 * @address: Memory address pulled from register
 * 
 * Return: Number of characters written to buffer (excluding null terminator)
 */
size_t
read_str_from_reg(
	char* buffer, 
	const pid_t pid, 
	const unsigned long address
)
{
	long peek_val;
	size_t chars_written = 0, unpacked_count = 0, word_count = 0;
	char unpacked_chars[sizeof(unsigned long) + 1] = { '\0' };

	/* PTRACE_PEEKDATA request until it returns 0 */
	while ((peek_val = ptrace(
		PTRACE_PEEKDATA,
		pid,
		address + (word_count * sizeof(unsigned long)),
		NULL
	)))
	{
		++word_count;

		/* Unpack peek_val into unpacked_chars */
		memcpy(unpacked_chars, &peek_val, sizeof(unsigned long));

		unpacked_count = sprintf(
			buffer,
			"%s",
			unpacked_chars
		);

		/* Advance buffer pointer and add to total char count */
		buffer += unpacked_count;
		chars_written += unpacked_count;

		/* If fewer than 8 chars unpacked, then you hit a null terminator */
		if (unpacked_count < sizeof(unsigned long))
			break;
	}

	return (chars_written);
}

/**
 * read_int_from_reg - Writes appropriately formatted integer to buffer
 * @buffer: char buffer to write string to
 * @reg_val: Value from register to cast/print
 * @int_type: type_t enum member indicating syscall parameter/return type
 * 
 * Return: Number of characters written to buffer (excluding null terminator)
 */
size_t
read_int_from_reg(
	char* buffer,
	const unsigned long reg_val,
	const type_t int_type
)
{
	size_t chars_written;

	switch (int_type)
	{
	case INT:
	case PID_T:
		chars_written = sprintf(buffer, "%d", (int)reg_val);
		break;
	case LONG:
	case SSIZE_T:
		chars_written = sprintf(buffer, "%ld", (long)reg_val);
		break;
	case UINT32_T:
	case UNSIGNED_INT:
		chars_written = sprintf(buffer, "%u", (unsigned int)reg_val);
		break;
	case UNSIGNED_LONG:
	case U64:
	case SIZE_T:
		chars_written = sprintf(buffer, "%lu", reg_val);
		break;
	default:
		chars_written = 0;
		break;
	}

	return (chars_written);
}

size_t
read_mmap_prot(
	char* buffer,
	const unsigned long reg_val
)
{
	size_t chars_written = 0;

	if (reg_val == PROT_NONE)
	{
		chars_written = sprintf(
			buffer,
			"PROT_NONE"
		);

		return (chars_written);
	}

	if (reg_val & PROT_READ)
	{
		chars_written += sprintf(
			buffer + chars_written,
			"PROT_READ|"
		);
	}
	if (reg_val & PROT_WRITE)
	{
		chars_written += sprintf(
			buffer + chars_written,
			"PROT_WRITE|"
		);
	}
	if (reg_val & PROT_EXEC)
	{
		chars_written += sprintf(
			buffer + chars_written,
			"PROT_EXEC|"
		);
	}

	/* Trim trailing pipe char */
	buffer[--chars_written] = '\0';
	return (chars_written);
}

size_t
read_mmap_flags(
	char* buffer,
	const unsigned long reg_val
)
{
	size_t chars_written = 0;

	/* Required flag: lowest bits 01, 11, or 10 */
	switch (reg_val & 3)
	{
	case MAP_SHARED:
		chars_written += sprintf(
			buffer + chars_written,
			"MAP_SHARED|"
		);
		break;
	case MAP_SHARED_VALIDATE:
		chars_written += sprintf(
			buffer + chars_written,
			"MAP_SHARED_VALIDATE|"
		);
		break;
	case MAP_PRIVATE:
		chars_written += sprintf(
			buffer + chars_written,
			"MAP_PRIVATE|"
		);
		break;
	}

	/* Handle optional flags here */

	buffer[--chars_written] = '\0';
	return (chars_written);
}

size_t
read_open_flags(
	char* buffer, 
	const pid_t pid, 
	const unsigned long reg_val
)
{
	/* TODO */
}

size_t
read_access_flags(
	char* buffer, 
	const pid_t pid, 
	const unsigned long reg_val
)
{
	/* TODO */
}
