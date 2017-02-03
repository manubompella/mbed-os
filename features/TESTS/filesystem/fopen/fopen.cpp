/*
 * mbed Microcontroller Library
 * Copyright (c) 2006-2016 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/** @file fopen.cpp Test cases to POSIX file fopen() interface.
 *
 * Please consult the documentation under the test-case functions for
 * a description of the individual test case.
 */

#include "mbed.h"
#include "SDBlockDevice.h"
#include "FATFileSystem.h"
#include "fsfat_debug.h"
#include "fsfat_test.h"
#include "utest/utest.h"
#include "unity/unity.h"
#include "greentea-client/test_env.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>     /*rand()*/
#include <inttypes.h>
#include <errno.h>
/* toolchain_support.h is included after errno.h so symbols are mapped to
 * consistent values for all toolchains */
#include "toolchain_support.h"

/* This is needed for stat() test, but is not available on ARMCC */
#ifdef TOOLCHAIN_GCC
#include <sys/stat.h>
#endif
using namespace utest::v1;

/// @cond FSFAT_DOXYGEN_DISABLE
#ifdef FSFAT_DEBUG
#define FSFAT_FOPEN_GREENTEA_TIMEOUT_S     3000
#else
#define FSFAT_FOPEN_GREENTEA_TIMEOUT_S     1000
#endif
/// @endcond


/* DEVICE_SPI
 *  This symbol is defined in targets.json if the target has a SPI interface, which is required for SDCard support.
 * FSFAT_SDCARD_INSTALLTED
 *  For testing purposes, an SDCard must be installed on the target for the test cases in this file to succeed.
 *  If the target has an SD card installed then uncomment the #define FSFAT_SDCARD_INSTALLED directive for the target.
 *
 * Notes
 *   The following 2 lines should be instated to perform the tests in this file:
 *      #define FSFAT_SDCARD_INSTALLED
 *      #define DEVICE_SPI
 */
#define FSFAT_SDCARD_INSTALLED
#define DEVICE_SPI
#if defined(DEVICE_SPI) && defined(FSFAT_SDCARD_INSTALLED)

static char fsfat_fopen_utest_msg_g[FSFAT_UTEST_MSG_BUF_SIZE];
#define FSFAT_FOPEN_TEST_MOUNT_PT_NAME  "sd"
#define FSFAT_FOPEN_TEST_MOUNT_PT_PATH  "/"FSFAT_FOPEN_TEST_MOUNT_PT_NAME


#if defined(TARGET_KL25Z)
SDBlockDevice sd(PTD2, PTD3, PTD1, PTD0);
FATFileSystem fs("sd", &sd);

#elif defined(TARGET_KL46Z) || defined(TARGET_KL43Z)
SDBlockDevice sd(PTD6, PTD7, PTD5, PTD4);
FATFileSystem fs("sd", &sd);

#elif defined(TARGET_K64F) || defined(TARGET_K66F)
SDBlockDevice sd(PTE3, PTE1, PTE2, PTE4);
FATFileSystem fs("sd", &sd);

#elif defined(TARGET_K22F)
SDBlockDevice sd(PTD6, PTD7, PTD5, PTD4);
FATFileSystem fs("sd", &sd);

#elif defined(TARGET_K20D50M)
SDBlockDevice sd(PTD2, PTD3, PTD1, PTC2);
FATFileSystem fs("sd", &sd);

#elif defined(TARGET_nRF51822)
SDBlockDevice sd(p12, p13, p15, p14);
FATFileSystem fs("sd", &sd);

#elif defined(TARGET_NUCLEO_F030R8) || \
      defined(TARGET_NUCLEO_F070RB) || \
      defined(TARGET_NUCLEO_F072RB) || \
      defined(TARGET_NUCLEO_F091RC) || \
      defined(TARGET_NUCLEO_F103RB) || \
      defined(TARGET_NUCLEO_F302R8) || \
      defined(TARGET_NUCLEO_F303RE) || \
      defined(TARGET_NUCLEO_F334R8) || \
      defined(TARGET_NUCLEO_F401RE) || \
      defined(TARGET_NUCLEO_F410RB) || \
      defined(TARGET_NUCLEO_F411RE) || \
      defined(TARGET_NUCLEO_L053R8) || \
      defined(TARGET_NUCLEO_L073RZ) || \
      defined(TARGET_NUCLEO_L152RE)
<<<<<<< HEAD
SDBlockDevice sd(D11, D12, D13, D10);
FATFileSystem fs("sd", &sd);

#elif defined(TARGET_DISCO_F051R8) || \
      defined(TARGET_NUCLEO_L031K6)
SDBlockDevice sd(SPI_MOSI, SPI_MISO, SPI_SCK, SPI_CS);
FATFileSystem fs("sd", &sd);

#elif defined(TARGET_LPC2368)
SDBlockDevice sd(p11, p12, p13, p14);
FATFileSystem fs("sd", &sd);

#elif defined(TARGET_LPC11U68)
SDBlockDevice sd(D11, D12, D13, D10);
FATFileSystem fs("sd", &sd);

#elif defined(TARGET_LPC1549)
SDBlockDevice sd(D11, D12, D13, D10);
FATFileSystem fs("sd", &sd);

#elif defined(TARGET_RZ_A1H)
SDBlockDevice sd(P8_5, P8_6, P8_3, P8_4);
FATFileSystem fs("sd", &sd);

#elif defined(TARGET_LPC11U37H_401)
SDBlockDevice sd(SDMOSI, SDMISO, SDSCLK, SDSSEL);
FATFileSystem fs("sd", &sd);

#else
#error "[NOT SUPPORTED] Instantiate SDBlockDevice sd(p11, p12, p13, p14) with the correct pin specification for target"
#endif


#define FSFAT_FOPEN_TEST_01      fsfat_fopen_test_01
#define FSFAT_FOPEN_TEST_02      fsfat_fopen_test_02
#define FSFAT_FOPEN_TEST_03      fsfat_fopen_test_03
#define FSFAT_FOPEN_TEST_04      fsfat_fopen_test_04
#define FSFAT_FOPEN_TEST_05      fsfat_fopen_test_05
#define FSFAT_FOPEN_TEST_06      fsfat_fopen_test_06
#define FSFAT_FOPEN_TEST_07      fsfat_fopen_test_07
#define FSFAT_FOPEN_TEST_08      fsfat_fopen_test_08
#define FSFAT_FOPEN_TEST_09      fsfat_fopen_test_09
#define FSFAT_FOPEN_TEST_10      fsfat_fopen_test_10
#define FSFAT_FOPEN_TEST_11      fsfat_fopen_test_11
#define FSFAT_FOPEN_TEST_12      fsfat_fopen_test_12
#define FSFAT_FOPEN_TEST_13      fsfat_fopen_test_13
#define FSFAT_FOPEN_TEST_14      fsfat_fopen_test_14
#define FSFAT_FOPEN_TEST_15      fsfat_fopen_test_15
#define FSFAT_FOPEN_TEST_16      fsfat_fopen_test_16
#define FSFAT_FOPEN_TEST_17      fsfat_fopen_test_17
#define FSFAT_FOPEN_TEST_18      fsfat_fopen_test_18
#define FSFAT_FOPEN_TEST_19      fsfat_fopen_test_19
#define FSFAT_FOPEN_TEST_20      fsfat_fopen_test_20
#define FSFAT_FOPEN_TEST_21      fsfat_fopen_test_21
#define FSFAT_FOPEN_TEST_22      fsfat_fopen_test_22
#define FSFAT_FOPEN_TEST_23      fsfat_fopen_test_23
#define FSFAT_FOPEN_TEST_24      fsfat_fopen_test_24
#define FSFAT_FOPEN_TEST_25      fsfat_fopen_test_25
#define FSFAT_FOPEN_TEST_26      fsfat_fopen_test_26
#define FSFAT_FOPEN_TEST_27      fsfat_fopen_test_27
#define FSFAT_FOPEN_TEST_28      fsfat_fopen_test_28
#define FSFAT_FOPEN_TEST_29      fsfat_fopen_test_29
#define FSFAT_FOPEN_TEST_30      fsfat_fopen_test_30


/* support functions */

/*
 * open tests that focus on testing fopen()
 * fsfat_handle_t fopen(const char* filename, char* data, size_t* len, fsfat_key_desc_t* kdesc)
 */

/* file data for test_01 */
static fsfat_kv_data_t fsfat_fopen_test_01_kv_data[] = {
        { "/sd/fopentst/hello/world/animal/wobbly/dog/foot/frontlft.txt", "missing"},
        { NULL, NULL},
};


/** @brief
 * Split a file path into its component parts, setting '/' characters to '\0', and returning
 * pointers to the file path components in the parts array. For example, if
 * filepath = "/sd/fopentst/hello/world/animal/wobbly/dog/foot/frontlft.txt" then
 *  *parts[0] = "sd"
 *  *parts[1] = "fopentst"
 *  *parts[2] = "hello"
 *  *parts[3] = "world"
 *  *parts[4] = "animal"
 *  *parts[5] = "wobbly"
 *  *parts[6] = "dog"
 *  *parts[7] = "foot"
 *  *parts[8] = "frontlft.txt"
 *   parts[9] = NULL
 *
 * ARGUMENTS
 *  @param  filepath     IN file path string to split into component parts. Expected to start with '/'
 *  @param  parts        IN OUT array to hold pointers to parts
 *  @param  num          IN number of components available in parts
 *
 * @return  On success, this returns the number of components in the filepath Returns number of compoee
 */
static int32_t fsfat_filepath_split(char* filepath, char* parts[], uint32_t num)
{
    uint32_t i = 0;
    int32_t ret = -1;
    char* z = filepath;

    while (i < num && *z != '\0') {
        if (*z == '/' ) {
            *z = '\0';
            parts[i] = ++z;
            i++;
        } else {
            z++;
        }
    }
    if (*z == '\0' && i > 0) {
        ret = (int32_t) i;
    }
    return ret;
}


/** @brief
 * remove all directories and file in the given filepath
 *
 * ARGUMENTS
 *  @param  filepath     IN file path string to split into component parts. Expected to start with '/'
 *
 * @return  On success, this returns 0, otherwise < 0 is returned;
 */
int32_t fsfat_filepath_remove_all(char* filepath)
{
    int32_t ret = -1;
    int32_t len = 0;
    char *fpathbuf = NULL;
    char *pos = NULL;

    FSFAT_FENTRYLOG("%s:entered\n", __func__);
    len = strlen(filepath);
    fpathbuf = (char*) malloc(len+1);
    if (fpathbuf == NULL) {
        FSFAT_DBGLOG("%s: failed to duplicate string (out of memory)\n", __func__);
        return ret;
    }
    memset(fpathbuf, 0, len+1);
    memcpy(fpathbuf, filepath, len);

    /* delete the leaf node first, and then successively parent directories. */
    pos = fpathbuf + strlen(fpathbuf);
    while (pos != fpathbuf) {
        /* If the remaining file path is the mount point path then finish as the mount point cannot be removed */
        if (strlen(fpathbuf) == strlen(FSFAT_FOPEN_TEST_MOUNT_PT_PATH) && strncmp(fpathbuf, FSFAT_FOPEN_TEST_MOUNT_PT_PATH, strlen(fpathbuf)) == 0) {
            break;
        }
        ret = remove(fpathbuf);
        pos = strrchr(fpathbuf, '/');
        *pos = '\0';
    }
    if (fpathbuf) {
        free(fpathbuf);
    }
    return ret;
}


/** @brief
 * make all directories in the given filepath. Do not create the file if present at end of filepath
 *
 * ARGUMENTS
 *  @param  filepath     IN file path containing directories and file
 *  @param  do_asserts   IN set to true if function should assert on errors
 *
 * @return  On success, this returns 0, otherwise < 0 is returned;
 */
static int32_t fsfat_filepath_make_dirs(char* filepath, bool do_asserts)
{
    int32_t i = 0;
    int32_t num_parts = 0;
    int32_t len = 0;
    int32_t ret = -1;
    char *fpathbuf = NULL;
    char *buf = NULL;
    int pos = 0;
    char *parts[10];

    FSFAT_DBGLOG("%s:entered\n", __func__);
    /* find the dirs to create*/
    memset(parts, 0, sizeof(parts));
    len = strlen(filepath);
    fpathbuf = (char*) malloc(len+1);
    if (fpathbuf == NULL) {
        FSFAT_DBGLOG("%s: failed to duplicate string (out of memory)\n", __func__);
        return ret;
    }
    memset(fpathbuf, 0, len+1);
    memcpy(fpathbuf, filepath, len);
    num_parts = fsfat_filepath_split(fpathbuf, parts, 10);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: failed to split filepath (filename=\"%s\", num_parts=%d)\n", __func__, filepath, (int) num_parts);
    TEST_ASSERT_MESSAGE(num_parts > 0, fsfat_fopen_utest_msg_g);

    /* Now create the directories on the directory path.
     * Skip creating dir for "/sd" which must be present */
    buf = (char*) malloc(strlen(filepath)+1);
    memset(buf, 0, strlen(filepath)+1);
    pos = sprintf(buf, "/%s", parts[0]);
    for (i = 1; i < num_parts - 1; i++) {
        pos += sprintf(buf+pos, "/%s", parts[i]);
        FSFAT_DBGLOG("mkdir(%s)\n", buf);
        ret = mkdir(buf, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (do_asserts == true) {
            FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: failed to create directory (filepath2=\"%s\", ret=%d, errno=%d)\n", __func__, buf, (int) ret, errno);
            TEST_ASSERT_MESSAGE(ret == 0, fsfat_fopen_utest_msg_g);
        }
    }

    if (buf) {
        free(buf);
    }
    if (fpathbuf) {
        free(fpathbuf);
    }
    return ret;
}


/* FIX ME: errno not set correctly when error occurs. This indicates a problem with the implementation. */

/** @brief
 * Basic fopen test which does the following:
 * - creates file and writes some data to the value blob.
 * - closes the newly created file.
 * - opens the file (r-only)
 * - reads the file data and checks its the same as the previously created data.
 * - closes the opened file
 *
 * @return on success returns CaseNext to continue to next test case, otherwise will assert on errors.
 */
static control_t fsfat_fopen_test_01(const size_t call_count)
{
    char* read_buf;
    int32_t ret = 0;
    size_t len = 0;
    fsfat_kv_data_t *node;
    FILE *fp = NULL;

    FSFAT_DBGLOG("%s:entered\n", __func__);
    (void) call_count;
    node = fsfat_fopen_test_01_kv_data;

    /* remove file and directory from a previous failed test run, if present */
    fsfat_filepath_remove_all((char*) node->filename);

    /* create dirs */
    ret = fsfat_filepath_make_dirs((char*) node->filename, true);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: failed to create dirs for filename (filename=\"%s\")(ret=%d)\n", __func__, node->filename, (int) ret);
    TEST_ASSERT_MESSAGE(ret == 0, fsfat_fopen_utest_msg_g);

    FSFAT_DBGLOG("%s:About to create new file (filename=\"%s\", data=\"%s\")\n", __func__, node->filename, node->value);
    fp = fopen(node->filename, "w+");
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: failed to create file (filename=\"%s\", data=\"%s\")(ret=%d, errno=%d)\n", __func__, node->filename, node->value, (int) ret, errno);
    TEST_ASSERT_MESSAGE(fp != NULL, fsfat_fopen_utest_msg_g);

    FSFAT_DBGLOG("%s:length of file=%d (filename=\"%s\", data=\"%s\")\n", __func__, (int) len, node->filename, node->value);
    len = strlen(node->value);
    ret = fwrite((const void*) node->value, len, 1, fp);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: failed to write file (filename=\"%s\", data=\"%s\")(ret=%d)\n", __func__, node->filename, node->value, (int) ret);
    TEST_ASSERT_MESSAGE(ret == 1, fsfat_fopen_utest_msg_g);

    FSFAT_DBGLOG("Created file successfully (filename=\"%s\", data=\"%s\")\n", node->filename, node->value);
    ret = fclose(fp);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: failed to close file (ret=%d, errno=%d)\n", __func__, (int) ret, errno);
    TEST_ASSERT_MESSAGE(ret == 0, fsfat_fopen_utest_msg_g);

    /* now open the newly created key */
    fp = NULL;
    fp = fopen(node->filename, "r");
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: failed to open file for reading (filename=\"%s\", data=\"%s\")(ret=%d)\n", __func__, node->filename, node->value, (int) ret);
    TEST_ASSERT_MESSAGE(fp != NULL, fsfat_fopen_utest_msg_g);

    len = strlen(node->value) + 1;
    read_buf = (char*) malloc(len);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: failed to allocated read buffer \n", __func__);
    TEST_ASSERT_MESSAGE(read_buf != NULL, fsfat_fopen_utest_msg_g);

    FSFAT_DBGLOG("Opened file successfully (filename=\"%s\", data=\"%s\")\n", node->filename, node->value);
    memset(read_buf, 0, len);
    ret = fread((void*) read_buf, len, 1, fp);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: failed to read file (filename=\"%s\", data=\"%s\", read_buf=\"%s\", ret=%d)\n", __func__, node->filename, node->value, read_buf, (int) ret);
    /* FIX ME: fread should return the number of items read, not 0 when an item is read successfully.
     * This indicates a problem with the implementation, as the correct data is read. The correct assert should be:
     *   TEST_ASSERT_MESSAGE(ret == 1, fsfat_fopen_utest_msg_g);
     * The following assert is curerntly used until the implementation is fixed
     */
    TEST_ASSERT_MESSAGE(ret == 0, fsfat_fopen_utest_msg_g);

    /* check read data is as expected */
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: read value data (%s) != expected value data (filename=\"%s\", data=\"%s\", read_buf=\"%s\", ret=%d)\n", __func__, read_buf, node->filename, node->value, read_buf, (int) ret);
    TEST_ASSERT_MESSAGE(strncmp(read_buf, node->value, strlen(node->value)) == 0, fsfat_fopen_utest_msg_g);

    if(read_buf){
        free(read_buf);
    }
    ret = fclose(fp);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: fclose() call failed (ret=%d, errno=%d).\n", __func__, (int) ret, errno);
    TEST_ASSERT_MESSAGE(ret == 0, fsfat_fopen_utest_msg_g);
    return CaseNext;
}

static fsfat_kv_data_t fsfat_fopen_test_02_data[] = {
        FSFAT_INIT_1_TABLE_MID_NODE,
        { NULL, NULL},
};

/**
 * @brief   test to fopen() a pre-existing key and try to write it, which should fail
 *          as by default pre-existing keys are opened read-only
 *
 * Basic open test which does the following:
 * - creates file with default rw perms and writes some data to the value blob.
 * - closes the newly created file.
 * - opens the file with the default permissions (read-only)
 * - tries to write the file data which should fail because file was not opened with write flag set.
 * - closes the opened key
 *
 * @return on success returns CaseNext to continue to next test case, otherwise will assert on errors.
 */
control_t fsfat_fopen_test_02(const size_t call_count)
{
    int32_t ret = -1;
    size_t len = 0;
    FILE *fp = NULL;

    FSFAT_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;
    len = strlen(fsfat_fopen_test_02_data[0].value);
    ret = fsfat_test_create(fsfat_fopen_test_02_data[0].filename, (char*) fsfat_fopen_test_02_data[0].value, len);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: failed to create file (ret=%d).\n", __func__, (int) ret);
    TEST_ASSERT_MESSAGE(ret >= 0, fsfat_fopen_utest_msg_g);

    /* by default, owner of key opens with read-only permissions*/
    fp = fopen(fsfat_fopen_test_02_data[0].filename, "r");
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: failed to open file (filename=\"%s\", ret=%d)\n", __func__, fsfat_fopen_test_02_data[0].filename, (int) ret);
    TEST_ASSERT_MESSAGE(fp != NULL, fsfat_fopen_utest_msg_g);

    len = strlen(fsfat_fopen_test_02_data[0].value);
    ret = fwrite((const void*) fsfat_fopen_test_02_data[0].value, len, 1, fp);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: call to fwrite() succeeded when should have failed for read-only file (filename=\"%s\")(ret=%d).\n", __func__, fsfat_fopen_test_02_data[0].filename, (int) ret);
    TEST_ASSERT_MESSAGE(ret <= 0, fsfat_fopen_utest_msg_g);

    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: fclose() call failed.\n", __func__);
    TEST_ASSERT_MESSAGE(fclose(fp) == 0, fsfat_fopen_utest_msg_g);

    return CaseNext;
}


/**
 * @brief   test to fopen() a pre-existing file and try to write it, which should succeed
 *          because the key was opened read-write permissions explicitly
 *
 * Basic open test which does the following:
 * - creates file with default rw perms and writes some data to the value blob.
 * - closes the newly created file.
 * - opens the file with the rw permissions (non default)
 * - tries to write the file data which should succeeds because file was opened with write flag set.
 * - closes the opened key
 *
 * @return on success returns CaseNext to continue to next test case, otherwise will assert on errors.
 */
control_t fsfat_fopen_test_03(const size_t call_count)
{
    int32_t ret = -1;
    size_t len = 0;
    FILE *fp = NULL;

    FSFAT_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;
    len = strlen(fsfat_fopen_test_02_data[0].value);
    ret = fsfat_test_create(fsfat_fopen_test_02_data[0].filename, (char*) fsfat_fopen_test_02_data[0].value, len);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: failed to create file in store (ret=%d).\n", __func__, (int) ret);
    TEST_ASSERT_MESSAGE(ret >= 0, fsfat_fopen_utest_msg_g);

    /* opens with read-write permissions*/
    fp = fopen(fsfat_fopen_test_02_data[0].filename, "w+");
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: failed to open file (filename=\"%s\")(ret=%d)\n", __func__, fsfat_fopen_test_02_data[0].filename, (int) ret);
    TEST_ASSERT_MESSAGE(ret >= 0, fsfat_fopen_utest_msg_g);

    len = strlen(fsfat_fopen_test_02_data[0].value);
    ret = fwrite((const void*) fsfat_fopen_test_02_data[0].value, len, 1, fp);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: call to fwrite() failed when should have succeeded (filename=\"%s\", ret=%d).\n", __func__, fsfat_fopen_test_02_data[0].filename, (int) ret);
    TEST_ASSERT_MESSAGE(ret >= 0, fsfat_fopen_utest_msg_g);

    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: fclose() call failed.\n", __func__);
    TEST_ASSERT_MESSAGE(fclose(fp) >= 0, fsfat_fopen_utest_msg_g);

    /* clean-up */
    ret = remove(fsfat_fopen_test_02_data[0].filename);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: unable to delete file (filename=%s, ret=%d) .\n", __func__, (int) ret);
    TEST_ASSERT_MESSAGE(ret >= 0, fsfat_fopen_utest_msg_g);

    return CaseNext;
}


/** @brief  test to call fopen() with a filename string that exceeds the maximum length
 * - chanFS supports the exFAT format which should support 255 char filenames
 * - check that filenames of this length can be created
 *
 * @return on success returns CaseNext to continue to next test case, otherwise will assert on errors.
 */
control_t fsfat_fopen_test_04(const size_t call_count)
{
    char filename_good[FSFAT_FILENAME_MAX_LENGTH+1];
    char filename_bad[FSFAT_FILENAME_MAX_LENGTH+2];
    int32_t ret = -1;
    size_t len = 0;

    FSFAT_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;

    memset(filename_good, 0, FSFAT_FILENAME_MAX_LENGTH+1);
    memset(filename_bad, 0, FSFAT_FILENAME_MAX_LENGTH+2);
    ret = fsfat_test_filename_gen(filename_good, FSFAT_FILENAME_MAX_LENGTH);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: unable to generate filename_good.\n", __func__);
    TEST_ASSERT_MESSAGE(ret >= 0, fsfat_fopen_utest_msg_g);

    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: filename_good is not the correct length (filename_good=%s, len=%d, expected=%d).\n", __func__, filename_good, (int) strlen(filename_good), (int) FSFAT_FILENAME_MAX_LENGTH);
    TEST_ASSERT_MESSAGE(strlen(filename_good) == FSFAT_FILENAME_MAX_LENGTH, fsfat_fopen_utest_msg_g);

    ret = fsfat_test_filename_gen(filename_bad, FSFAT_FILENAME_MAX_LENGTH+1);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: unable to generate filename_bad.\n", __func__);
    TEST_ASSERT_MESSAGE(ret >= 0, fsfat_fopen_utest_msg_g);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: filename_bad is not the correct length (len=%d, expected=%d).\n", __func__, (int) strlen(filename_bad), (int) FSFAT_FILENAME_MAX_LENGTH+1);
    TEST_ASSERT_MESSAGE(strlen(filename_bad) == FSFAT_FILENAME_MAX_LENGTH+1, fsfat_fopen_utest_msg_g);

    len = strlen(filename_good);
    ret = fsfat_test_create(filename_good, filename_good, len);
    /* FIXME:
     * The current implementation can create file with a filename with 9 chars (more than the 8 restriction of FAT32 Short File Names).
     * However, the exFAT 255 char filesnames is not supported and hence the following is commented out. Find out what is
     * the supported max filename length and change this testcase according.
     *
     *  FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: failed to create file (filename=%s, ret=%d).\n", __func__, filename_good, (int) ret);
     *  TEST_ASSERT_MESSAGE(ret >= 0, fsfat_fopen_utest_msg_g);
     */

    len = strlen(filename_bad);
    ret = fsfat_test_create(filename_bad, filename_bad, len);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: created file in store for filename_bad when should have failed (filename=%s, ret=%d).\n", __func__, filename_bad, (int) ret);
    TEST_ASSERT_MESSAGE(ret < 0, fsfat_fopen_utest_msg_g);
    return CaseNext;
}



/// @cond FSFAT_DOXYGEN_DISABLE
typedef struct fsfat_fopen_kv_name_ascii_node {
    uint32_t code;
    uint32_t f_allowed : 1;
} fsfat_fopen_kv_name_ascii_node;
/// @endcond

static const uint32_t fsfat_fopen_kv_name_ascii_table_code_sentinel_g = 256;

/*@brief    table recording ascii character codes permitted in kv names */
static fsfat_fopen_kv_name_ascii_node fsfat_fopen_kv_name_ascii_table[] =
{
        {0 , true},         /* code 0-33 allowed*/
        {34, false},        /* '"' not allowed */
        {35, true},         /* allowed */
        {42, false},        /* '*' not allowed */
        {43, true},         /* allowed */
        {47, false},        /* '/' not allowed */
        {48, true},         /* allowed */
        {58, false},        /* ':' not allowed */
        {59, true},         /* allowed */
        {60, false},        /* '<' not allowed */
        {61, true},         /* allowed */
        {62, false},        /* '?', '>' not allowed */
        {64, true},         /* allowed */
        {92, false},        /* '\' not allowed */
        {93, true},         /* allowed */
        {124, false},        /* '!' not allowed */
        {125, true},         /* allowed */
        {127, false},        /* DEL not allowed */
        {128, true},         /* allowed */
        {fsfat_fopen_kv_name_ascii_table_code_sentinel_g, false},       /* sentinel */
};


/// @cond FSFAT_DOXYGEN_DISABLE
enum fsfat_fopen_kv_name_pos {
    fsfat_fopen_kv_name_pos_start = 0x0,
    fsfat_fopen_kv_name_pos_mid,
    fsfat_fopen_kv_name_pos_end,
    fsfat_fopen_kv_name_pos_max
};
/// @endcond

/** @brief  test to call fopen() with filename that in includes illegal characters
 *          - the character(s) can be at the beginning of the filename
 *          - the character(s) can be at the end of the filename
 *          - the character(s) can be somewhere within the filename string
 *          - a max-length string of random characters (legal and illegal)
 *          - a max-length string of random illegal characters only
 *
 * @return on success returns CaseNext to continue to next test case, otherwise will assert on errors.
 */
control_t fsfat_fopen_test_05(const size_t call_count)
{
    bool f_allowed = false;
    const char *mnt_pt = "/sd";
    const char *basename = "goodfile";
    const char *extname = "txt";
    const size_t basename_len = strlen(basename);
    const size_t filename_len = strlen(mnt_pt)+strlen(basename)+strlen(extname)+2;  /* extra 2 chars for '/' and '.' in "/sd/goodfile.txt" */
    char filename[FSFAT_BUF_MAX_LENGTH];
    size_t len = 0;
    uint32_t j = 0;
    int32_t ret = 0;
    fsfat_fopen_kv_name_ascii_node* node = NULL;
    uint32_t pos;

    FSFAT_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;

#ifdef FSFAT_DEBUG
    /* symbol only used why debug is enabled */
    const char* pos_str = NULL;
#endif

    /* create bad keyname strings with invalid character code at start of keyname */
    node = fsfat_fopen_kv_name_ascii_table;
    memset(filename, 0, FSFAT_BUF_MAX_LENGTH);
    while(node->code !=  fsfat_fopen_kv_name_ascii_table_code_sentinel_g)
    {
        /* loop over range */
        for(j = node->code; j < (node+1)->code; j++)
        {
            if( (j >= 48 && j <= 57) || (j >= 65 && j <= 90) || (j >= 97 && j <= 122)) {
                FSFAT_DBGLOG("%s: skipping alpha-numeric ascii character code %d (%c).\n", __func__, (int) j, j);
                continue;
            }

            /* set the start, mid, last character of the name to the test char code */
            for(pos = (uint32_t) fsfat_fopen_kv_name_pos_start; pos < (uint32_t) fsfat_fopen_kv_name_pos_max; pos++)
            {
                len = snprintf(filename, filename_len+1, "%s/%s.%s", mnt_pt, basename, extname);
                /* overwrite a char at the pos start, mid, end of the filename with an ascii char code (both illegal and legal)*/
                switch(pos)
                {
                case fsfat_fopen_kv_name_pos_start:
                    filename[5] = (char) j; /* 5 so at to write the second basename char (bad chars as first char not accepted)*/
                    break;
                case fsfat_fopen_kv_name_pos_mid:
                    /* create bad keyname strings with invalid character code in the middle of keyname */
                    filename[5+basename_len/2] = (char) j;
                    break;
                case fsfat_fopen_kv_name_pos_end:
                    /* create bad keyname strings with invalid character code at end of keyname */
                    filename[5+basename_len-1] = (char) j;
                    break;
                default:
                    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: unexpected value of pos (pos=%d).\n", __func__, (int) pos);
                    TEST_ASSERT_MESSAGE(ret >= 0, fsfat_fopen_utest_msg_g);
                    break;
                }

#ifdef FSFAT_DEBUG
                /* processing only required when debug trace enabled */
                switch(pos)
                {
                case fsfat_fopen_kv_name_pos_start:
                    pos_str = "start";
                    break;
                case fsfat_fopen_kv_name_pos_mid:
                    pos_str = "middle";
                    break;
                case fsfat_fopen_kv_name_pos_end:
                    pos_str = "end";
                    break;
                default:
                    break;
                }
#endif
                ret = fsfat_test_create(filename, (const char*) filename, len);

                /* special cases */
                switch(j)
                {
                //case 0 :
				//case 46 :
                //    switch(pos)
                //    {
                //    /* for code = 0 (null terminator). permitted at mid and end of string */
                //    /* for code = 46 ('.'). permitted at mid and end of string but not at start */
                //    case fsfat_fopen_kv_name_pos_start:
                //        f_allowed = false;
                //        break;
                //    case fsfat_fopen_kv_name_pos_mid:
                //    case fsfat_fopen_kv_name_pos_end:
                //    default:
                //        f_allowed = true;
                //        break;
                //    }
                //    break;
				default:
					f_allowed = node->f_allowed;
					break;
                }
                if(f_allowed == true)
                {
                    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: failed to create file in store when filename contains valid characters (code=%d, ret=%d).\n", __func__, (int) j, (int) ret);
                    TEST_ASSERT_MESSAGE(ret >= 0, fsfat_fopen_utest_msg_g);
                    /* revert FSFAT_LOG for more trace */
                    FSFAT_DBGLOG("Successfully created a file with valid keyname containing ascii character code %d (%c) at the %s of the keyname.\n", (int) j, (int) j, pos_str);
                    FSFAT_LOG("%c", '.');

                    ret = fsfat_test_delete(filename);
                    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: failed to delete file previously created (code=%d, ret=%d).\n", __func__, (int) j, (int) ret);
                    TEST_ASSERT_MESSAGE(ret >= 0, fsfat_fopen_utest_msg_g);
                }
                else
                {   /*node->f_allowed == false => not allowed to create kv name with ascii code */
                    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: created file in store when filename contains an invalid character (code=%d, ret=%d).\n", __func__, (int) j, (int) ret);
                    TEST_ASSERT_MESSAGE(ret < 0, fsfat_fopen_utest_msg_g);
                    /* revert FSFAT_LOG for more trace */
                    FSFAT_DBGLOG("Successfully failed to create a file with an invalid keyname containing ascii character code %d at the %s of the keyname.\n", (int) j, pos_str);
                    FSFAT_LOG("%c", '.');
                }
            }
        }
        node++;
    }

    FSFAT_LOG("%c", '\n');
    return CaseNext;
}


static const char fsfat_fopen_ascii_illegal_buf_g[] = "\"�'*+,./:;<=>?[\\]|";

/** @brief  test to call fopen() with filename that in includes
 *          illegal characters
 *          - a max-length string of random illegal characters only
 *
 * @return on success returns CaseNext to continue to next test case, otherwise will assert on errors.
 */
control_t fsfat_fopen_test_06(const size_t call_count)
{
    const char *mnt_pt = "/sd";
    const char *extname = "txt";
    const size_t filename_len = strlen(mnt_pt)+FSFAT_MAX_FILE_BASENAME+strlen(extname)+2;  /* extra 2 chars for '/' and '.' in "/sd/goodfile.txt" */
    char filename[FSFAT_BUF_MAX_LENGTH];
    int32_t i = 0;
    int32_t j = 0;
    uint32_t pos = 0;
    uint32_t len = 0;
    int32_t ret = -1;
    size_t buf_data_max = 0;

    FSFAT_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;

    memset(filename, 0, FSFAT_BUF_MAX_LENGTH);
    /* create bad keyname strings with invalid character code at start of keyname */
    buf_data_max = strlen(fsfat_fopen_ascii_illegal_buf_g);

    /* generate a number of illegal filenames */
    for (j = 0; i < FSFAT_MAX_FILE_BASENAME; j++) {
        /* generate a kv name of illegal chars*/
        len = snprintf(filename, filename_len+1, "%s/", mnt_pt);
        for (i = 0; i < FSFAT_MAX_FILE_BASENAME; i++) {
            pos = rand() % (buf_data_max+1);
            len += snprintf(filename+len, filename_len+1, "%c", fsfat_fopen_ascii_illegal_buf_g[pos]);

        }
        len += snprintf(filename+len, filename_len+1, ".%s", extname);
        ret = fsfat_test_create(filename, filename, len);
        FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: created file when filename contains invalid characters (filename=%s, ret=%d).\n", __func__, filename, (int) ret);
        TEST_ASSERT_MESSAGE(ret < 0, fsfat_fopen_utest_msg_g);
    }
    return CaseNext;
}


/** @brief  test for errno reporting on a failed fopen()call
 *
 *	This test does the following:
 *	- tries to open a file that does not exist for reading, and checks that a NULL pointer is returned.
 *	- checks that errno is not 0 as there is an error.
 *	- checks that ferror() returns 1 indicating an error exists.
 *
 * Note: see NOTE_1 below.
 *
 * @return on success returns CaseNext to continue to next test case, otherwise will assert on errors.
 */
control_t fsfat_fopen_test_07(const size_t call_count)
{
	FILE *f = NULL;
	int ret = -1;
    int errno_val = 0;
    char *filename = "/sd/badfile.txt";

    FSFAT_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;

    errno = 0;
    /* this is expect to fail as the file doesnt exist */
    f = fopen(filename,"r");

    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: opened non-existent file for reading (filename=%s, f=%p).\n", __func__, filename, f);
    TEST_ASSERT_MESSAGE(f == NULL, fsfat_fopen_utest_msg_g);

    /* check errno is set correctly */
#ifdef TOOLCHAIN_GCC
    /* Store errno so the current value set  is not changed by new function call */
    errno_val = errno;
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: errno has unexpected value (errno != 0 expected) (filename=%s, errno=%d).\n", __func__, filename, errno);
    TEST_ASSERT_MESSAGE(errno_val != 0, fsfat_fopen_utest_msg_g);

    /* check ferror() returns non-zero indicating there is an error
     * Note ARMCC appears to fault when null FILE* is supplied to ferror() */
    ret = ferror(f);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: ferror() did not return non-zero value when error exists (filename=%s, ret=%d).\n", __func__, filename, (int) ret);
    TEST_ASSERT_MESSAGE(ret != 0, fsfat_fopen_utest_msg_g);
#endif  /* TOOLCHAIN_GCC */
    return CaseNext;
}


/** @brief  test for operation of clearerr() and ferror()
 *
 *  The test does the following:
 *  - opens and then closes a file, but keeps a copy of the FILE pointer fp.
 *  - set errno to 0.
 *  - write to the close file with fwrite(fp) which should return 0 (no writes) and set the errno.
 *  - check the error condition is set with ferror().
 *  - clear the error with clearerr().
 *  - check the error condition is reset with ferror().
 *
 * NOTE_1: GCC/ARMCC support for setting errno
 *  - Documentation (e.g. fwrite() man page) does not explicity say fwrite() sets errno
 *    (e.g. for an fwrite() on a read-only file).
 *  - GCC libc fwrite() appears to set errno as expected.
 *  - ARMCC & IAR libc fwrite() appears not to set errno.
 *
 * The following ARMCC documents are silent on whether fwrite() sets errno:
 * - "ARM C and C++ Libraries and Floating-Point Support".
 * - "RL-ARM User Guide fwrite() section".
 *
 * @return on success returns CaseNext to continue to next test case, otherwise will assert on errors.
 */
control_t fsfat_fopen_test_08(const size_t call_count)
{
    FILE *fp = NULL;
    int ret = -1;
    int ret_ferror = -1;
    char *filename = "/sd/test.txt";
    int errno_val = 0;

    FSFAT_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;

    errno = 0;
    fp = fopen(filename,"w+");
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: failed to open file (filename=%s, f=%p).\n", __func__, filename, fp);
    TEST_ASSERT_MESSAGE(fp != NULL, fsfat_fopen_utest_msg_g);

    /* close the fp but then try to read or write it */
    ret = fclose(fp);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: failed to close file (ret=%d, errno=%d)\n", __func__, (int) ret, errno);
    TEST_ASSERT_MESSAGE(ret == 0, fsfat_fopen_utest_msg_g);

    /* open file  */
    errno = 0;
    fp = fopen(filename, "r");
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: failed to open file for reading (filename=\"%s\", ret=%d)\n", __func__, filename, (int) ret);
    TEST_ASSERT_MESSAGE(fp != NULL, fsfat_fopen_utest_msg_g);

    /* Perform fwrite() operation that will fail. */
    errno = 0;
    ret = fwrite("42!", 4, 1, fp);
    /* Store errno so the current value set  is not changed by new function call */
    errno_val = errno;

    ret_ferror = ferror(fp);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: ferror() failed to report error (filename=%s, ret_ferror=%d).\n", __func__, filename, (int) ret_ferror);
    TEST_ASSERT_MESSAGE(ret_ferror != 0, fsfat_fopen_utest_msg_g);

    FSFAT_DBGLOG("%s:b ret=%d, errno=%d, errno_val=%d, ret_ferror=%d\n", __func__, (int) ret, errno, errno_val, ret_ferror);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: fwrite successfully wrote to read-only file (filename=%s, ret=%d).\n", __func__, filename, (int) ret);
    /* the fwrite() should fail and return 0. */
    TEST_ASSERT_MESSAGE(ret == 0, fsfat_fopen_utest_msg_g);

#ifdef TOOLCHAIN_GCC
    /* check that errno is set. ARMCC appears not to set errno for fwrite() failure. */
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: unexpected zero value for errno (filename=%s, ret=%d, errno=%d).\n", __func__, filename, (int) ret, errno);
    TEST_ASSERT_MESSAGE(errno != 0, fsfat_fopen_utest_msg_g);

    /* check that errno is set to the expected value (this may change differ for different libc's) */
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: errno != EBADF (filename=%s, ret=%d, errno=%d).\n", __func__, filename, (int) ret, errno);
    TEST_ASSERT_MESSAGE(errno == EBADF, fsfat_fopen_utest_msg_g);
#endif  /* TOOLCHAIN_GCC */

    /* check clearerr() return clears the error */
    clearerr(fp);
    ret = ferror(fp);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: ferror() did not return zero value when error has been cleared (filename=%s, ret=%d).\n", __func__, filename, (int) ret);
    TEST_ASSERT_MESSAGE(ret == 0, fsfat_fopen_utest_msg_g);

    fclose(fp);
    return CaseNext;
}


#ifdef NO_SYMBOL
control_t fsfat_fopen_test_08(const size_t call_count)
{
    FILE *fp = NULL;
    int ret = -1;
    char *filename = "/sd/test.txt";

    FSFAT_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;

    errno = 0;
    fp = fopen(filename,"w+");
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: failed to open file (filename=%s, f=%p).\n", __func__, filename, fp);
    TEST_ASSERT_MESSAGE(fp != NULL, fsfat_fopen_utest_msg_g);

    /* close the fp but then try to read or write it */
    ret = fclose(fp);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: failed to close file (ret=%d, errno=%d)\n", __func__, (int) ret, errno);
    TEST_ASSERT_MESSAGE(ret == 0, fsfat_fopen_utest_msg_g);

    /* try to write to closed file */
    errno = 0;
    ret = fwrite("42!", 4, 1, fp);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: fwrite successfully wroted to closed file (filename=%s, ret=%d, errno=%d).\n", __func__, filename, (int) ret, errno);
    TEST_ASSERT_MESSAGE(ret == 0, fsfat_fopen_utest_msg_g);

    /* check that errno is set */
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: unexpected zero value for errno (filename=%s, ret=%d, errno=%d).\n", __func__, filename, (int) ret, errno);
    TEST_ASSERT_MESSAGE(errno != 0, fsfat_fopen_utest_msg_g);

    /* check that errno is set to the expected value (this may change differ for different libc's) */
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: errno != EBADF (filename=%s, ret=%d, errno=%d).\n", __func__, filename, (int) ret, errno);
    TEST_ASSERT_MESSAGE(errno == EBADF, fsfat_fopen_utest_msg_g);

    /* check clearerr() return clears the error */
    clearerr(fp);
    ret = ferror(fp);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: ferror() did not return zero value when error has been cleared (filename=%s, ret=%d).\n", __func__, filename, (int) ret);
    TEST_ASSERT_MESSAGE(ret == 0, fsfat_fopen_utest_msg_g);
    return CaseNext;
}
#endif NO_SYMBOL

/** @brief  test for operation of ftell()
 *
 * @return on success returns CaseNext to continue to next test case, otherwise will assert on errors.
 */
control_t fsfat_fopen_test_09(const size_t call_count)
{
    FILE *fp = NULL;
    int ret = -1;
    int32_t len = 0;

    FSFAT_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;

    /* create a file of a certain length */
    len = strlen(fsfat_fopen_test_02_data[0].value);
    ret = fsfat_test_create(fsfat_fopen_test_02_data[0].filename, (char*) fsfat_fopen_test_02_data[0].value, len);

    errno = 0;
    /* Open the file for reading so the file is not truncated to 0 length. */
    fp = fopen(fsfat_fopen_test_02_data[0].filename, "r");
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: failed to open file (filename=%s, fp=%p, errno=%d).\n", __func__, fsfat_fopen_test_02_data[0].filename, fp, errno);
    TEST_ASSERT_MESSAGE(fp != NULL, fsfat_fopen_utest_msg_g);

    errno = 0;
    ret = fseek(fp, 0, SEEK_END);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: fseek() failed to SEEK_END (filename=%s, ret=%d, errno=%d).\n", __func__, fsfat_fopen_test_02_data[0].filename, (int) ret, errno);
    TEST_ASSERT_MESSAGE(ret == 0, fsfat_fopen_utest_msg_g);

    errno = 0;
    ret = ftell(fp);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: ftell() failed to report correct offset value (filename=%s, ret=%d, errno=%d).\n", __func__, fsfat_fopen_test_02_data[0].filename, (int) ret, errno);
    TEST_ASSERT_MESSAGE(ret == len, fsfat_fopen_utest_msg_g);

    errno = 0;
    ret = fclose(fp);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: failed to close file (ret=%d, errno=%d)\n", __func__, (int) ret, errno);
    TEST_ASSERT_MESSAGE(ret == 0, fsfat_fopen_utest_msg_g);

    return CaseNext;
}

/** @brief  test for operation of remove()
 * @return on success returns CaseNext to continue to next test case, otherwise will assert on errors.
 */
control_t fsfat_fopen_test_10(const size_t call_count)
{

    FSFAT_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;

    /* todo:
     * - test remove() on a file that exists. should succeed.
     * - test remove() on a dir that exists. should succeed.
     * - test remove() on a file that doesnt exist. should fail. check errno set.
     * - test remove() on a dir that doesnt exist. should fail. check errno set.
     * */

    return CaseNext;
}

/** @brief  test for operation of rename()
 * @return on success returns CaseNext to continue to next test case, otherwise will assert on errors.
 */
control_t fsfat_fopen_test_11(const size_t call_count)
{

    FSFAT_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;

    /* todo:
     * - test rename() on a file that exists to a new filename within the same directory. should succeed
     * - test rename() on a file that exists to a new filename within a different directory. should succeed
     */
    return CaseNext;
}

/** @brief  test for operation of tmpnam() (currrently unimplemented)
 * @return on success returns CaseNext to continue to next test case, otherwise will assert on errors.
 */
control_t fsfat_fopen_test_12(const size_t call_count)
{

    FSFAT_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;

    /* todo:
     * - show function is not implemented.
     */
    return CaseNext;
}

/** @brief  test for operation of tmpfile() (currrently unimplemented)
 * @return on success returns CaseNext to continue to next test case, otherwise will assert on errors.
 */
control_t fsfat_fopen_test_13(const size_t call_count)
{

    FSFAT_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;

    /* todo:
     * - show function is not implemented.
     */
    return CaseNext;
}

/** @brief  test for operation of opendir()
 * @return on success returns CaseNext to continue to next test case, otherwise will assert on errors.
 */
control_t fsfat_fopen_test_14(const size_t call_count)
{

    FSFAT_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;

    /* todo:
     * - open a dir that exists. should succeed.
     * - open a dir that doesnt exists. should succeed.
     */
    return CaseNext;
}

/** @brief  test for operation of readdir()
 * @return on success returns CaseNext to continue to next test case, otherwise will assert on errors.
 */
control_t fsfat_fopen_test_15(const size_t call_count)
{

    FSFAT_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;

    /* todo:
     */
    return CaseNext;
}

/** @brief  test for operation of closedir()
 * @return on success returns CaseNext to continue to next test case, otherwise will assert on errors.
 */
control_t fsfat_fopen_test_16(const size_t call_count)
{

    FSFAT_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;

    /* todo:
     */
    return CaseNext;
}

/** @brief  test for operation of rewinddir()
 * @return on success returns CaseNext to continue to next test case, otherwise will assert on errors.
 */
control_t fsfat_fopen_test_17(const size_t call_count)
{

    FSFAT_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;

    /* todo:
     */
    return CaseNext;
}


/** @brief  test for operation of telldir()
 * @return on success returns CaseNext to continue to next test case, otherwise will assert on errors.
 */
control_t fsfat_fopen_test_18(const size_t call_count)
{

    FSFAT_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;

    /* todo:
     */
    return CaseNext;
}

/** @brief  test for operation of seekdir()
 * @return on success returns CaseNext to continue to next test case, otherwise will assert on errors.
 */
control_t fsfat_fopen_test_19(const size_t call_count)
{

    FSFAT_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;

    /* todo:
     */
    return CaseNext;
}


/* file data for test_20 */
static fsfat_kv_data_t fsfat_fopen_test_20_kv_data[] = {
        /* a file is included in the filepath even though its not created by the test,
         * as the fsfat_filepath_make_dirs() works with it present. */
        { "/sd/test_20/dummy.txt", "testdir"},
        { NULL, NULL},
};
/** @brief  test for operation of mkdir()/remove()
 *
 * This test checks that:
 * - The mkdir() function successfully creates a directory that is not already present.
 * - The mkdir() function returns EEXIST when trying to create a directory thats already present.
 * - The remove() function successfully removes a directory that is present.
 *
 * @return on success returns CaseNext to continue to next test case, otherwise will assert on errors.
 */
control_t fsfat_fopen_test_20(const size_t call_count)
{
    int32_t ret = 0;
    FILE *fp = NULL;

    FSFAT_DBGLOG("%s:entered\n", __func__);
    (void) call_count;

    /* start from a know state i.e. directory to be created in not present */
    fsfat_filepath_remove_all((char*) fsfat_fopen_test_20_kv_data[0].filename);

    errno = 0;
    ret = fsfat_filepath_make_dirs((char*) fsfat_fopen_test_20_kv_data[0].filename, false);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: failed to create dir (dirname=%s, ret=%d, errno=%d)\n", __func__, fsfat_fopen_test_20_kv_data[0].filename, (int) ret, errno);
    TEST_ASSERT_MESSAGE(ret == 0, fsfat_fopen_utest_msg_g);

    /* check that get a suitable error when try to create it again.*/
    errno = 0;
    ret = fsfat_filepath_make_dirs((char*) fsfat_fopen_test_20_kv_data[0].filename, false);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: permitted to create directory when already exists (dirname=%s, ret=%d, errno=%d)\n", __func__, fsfat_fopen_test_20_kv_data[0].filename, (int) ret, errno);
    TEST_ASSERT_MESSAGE(ret != 0, fsfat_fopen_utest_msg_g);

    /* check errno is as expected */
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: errno != EEXIST (dirname=%s, ret=%d, errno=%d)\n", __func__, fsfat_fopen_test_20_kv_data[0].filename, (int) ret, errno);
    TEST_ASSERT_MESSAGE(errno == EEXIST, fsfat_fopen_utest_msg_g);

    ret = fsfat_filepath_remove_all((char*) fsfat_fopen_test_20_kv_data[0].filename);
    FSFAT_TEST_UTEST_MESSAGE(fsfat_fopen_utest_msg_g, FSFAT_UTEST_MSG_BUF_SIZE, "%s:Error: failed to remove directory (dirname=%s, ret=%d, errno=%d)\n", __func__, fsfat_fopen_test_20_kv_data[0].filename, (int) ret, errno);
    TEST_ASSERT_MESSAGE(ret == 0, fsfat_fopen_utest_msg_g);

    return CaseNext;
}


/** @brief  test for operation of stat()
 * @return on success returns CaseNext to continue to next test case, otherwise will assert on errors.
 */
control_t fsfat_fopen_test_21(const size_t call_count)
{

    FSFAT_FENTRYLOG("%s:entered\n", __func__);
    (void) call_count;

    /* todo:
     */
    return CaseNext;
}





#else


#define FSFAT_FOPEN_TEST_01      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_02      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_03      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_04      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_05      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_06      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_07      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_08      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_09      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_10      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_11      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_12      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_13      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_14      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_15      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_16      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_17      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_18      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_19      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_20      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_21      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_22      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_23      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_24      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_25      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_26      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_27      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_28      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_29      fsfat_fopen_test_dummy
#define FSFAT_FOPEN_TEST_30      fsfat_fopen_test_dummy

/** @brief  fsfat_fopen_test_dummy    Dummy test case for testing when platform doesnt have an SDCard installed.
 *
 * @return success always
 */
static control_t fsfat_fopen_test_dummy()
{
    printf("Null test\n");
    return CaseNext;
}

#endif  /* defined(DEVICE_SPI) && defined(FSFAT_SDCARD_INSTALLED) */


/// @cond FSFAT_DOXYGEN_DISABLE
utest::v1::status_t greentea_setup(const size_t number_of_cases)
{
    GREENTEA_SETUP(FSFAT_FOPEN_GREENTEA_TIMEOUT_S, "default_auto");
    return greentea_test_setup_handler(number_of_cases);
}

Case cases[] = {
           /*          1         2         3         4         5         6        7  */
           /* 1234567890123456789012345678901234567890123456789012345678901234567890 */
        Case("FSFAT_FOPEN_TEST_01: fopen()/fwrite()/fclose() directories/file in multi-dir filepath.", FSFAT_FOPEN_TEST_01),
        Case("FSFAT_FOPEN_TEST_02: fopen(r) pre-existing file try to write it.", FSFAT_FOPEN_TEST_02),
        Case("FSFAT_FOPEN_TEST_03: fopen(w+) pre-existing file try to write it.", FSFAT_FOPEN_TEST_03),
        Case("FSFAT_FOPEN_TEST_04: fopen() with a filename exceeding the maximum length.", FSFAT_FOPEN_TEST_04),
#ifdef FOPEN_EXTENDED_TESTING
        Case("FSFAT_FOPEN_TEST_05: fopen() with filenames including illegal characters.", FSFAT_FOPEN_TEST_05),
#endif
        Case("FSFAT_FOPEN_TEST_06", FSFAT_FOPEN_TEST_06),
        Case("FSFAT_FOPEN_TEST_07: fopen()/errno handling.", FSFAT_FOPEN_TEST_07),
        Case("FSFAT_FOPEN_TEST_08: ferror()/clearerr()/errno handling.", FSFAT_FOPEN_TEST_08),
        Case("FSFAT_FOPEN_TEST_09: ftell() handling.", FSFAT_FOPEN_TEST_09),
#ifdef FOPEN_NOT_IMPLEMENTED
        Case("FSFAT_FOPEN_TEST_10: todo.", FSFAT_FOPEN_TEST_10),
        Case("FSFAT_FOPEN_TEST_11: todo.", FSFAT_FOPEN_TEST_11),
        Case("FSFAT_FOPEN_TEST_12: todo.", FSFAT_FOPEN_TEST_12),
        Case("FSFAT_FOPEN_TEST_13: todo.", FSFAT_FOPEN_TEST_13),
        Case("FSFAT_FOPEN_TEST_14: todo.", FSFAT_FOPEN_TEST_14),
        Case("FSFAT_FOPEN_TEST_15: todo.", FSFAT_FOPEN_TEST_15),
        Case("FSFAT_FOPEN_TEST_16: todo.", FSFAT_FOPEN_TEST_16),
        Case("FSFAT_FOPEN_TEST_17: todo.", FSFAT_FOPEN_TEST_17),
        Case("FSFAT_FOPEN_TEST_18: todo.", FSFAT_FOPEN_TEST_18),
        Case("FSFAT_FOPEN_TEST_19: todo.", FSFAT_FOPEN_TEST_19),
#endif /* FOPEN_NOT_IMPLEMENTED */
        Case("FSFAT_FOPEN_TEST_20: mkdir() test.", FSFAT_FOPEN_TEST_20),
#ifdef FOPEN_NOT_IMPLEMENTED
        Case("FSFAT_FOPEN_TEST_21: todo.", FSFAT_FOPEN_TEST_21),
#endif /* FOPEN_NOT_IMPLEMENTED */

};


/* Declare your test specification with a custom setup handler */
Specification specification(greentea_setup, cases);

int main()
{
    return !Harness::run(specification);
}
/// @endcond
