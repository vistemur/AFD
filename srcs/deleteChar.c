void deleteChar(char* str, int pos)
{
    while (str[pos] != '\0') {
        str[pos] = str[pos + 1];
        pos++;
    }
}
