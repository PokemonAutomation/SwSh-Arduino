# Raid Code

This option is used by all the auto-hosts:
```
const uint8_t RANDOM_DIGITS     =   0;
const char* RAID_CODE           =   "1280 0000";
```
These two values let you set the raid code.

### No Code (FFA)
```
const uint8_t RANDOM_DIGITS     =   0;
const char* RAID_CODE           =   "";
```
### Fixed Code
```
const uint8_t RANDOM_DIGITS     =   0;
const char* RAID_CODE           =   "1234 5678";
```
This will always use the code “12345678” for every raid.

Notes:
- The program will skip non-digit characters. So the space or hyphen separator is optional.
- If the code is less than 8 digits, it will be padded out to 8 digits with zeros.

### Random Code:
```
const uint8_t RANDOM_DIGITS     =   4;
const char* RAID_CODE           =   "1234 5678";
```
In this example, it will randomize the first 4 digits of the raid code. The remaining digits will be copies of the 4th digit.

For example: “12344444”, “78966666”, etc... The purpose of repeating the last digit is to make it easier for raiders to enter the code.

When using a random raid code, the contents of `RAID_CODE` are used to generate a starting seed for the RNG. If you don’t know what that means, just ignore it and leave it as is.

