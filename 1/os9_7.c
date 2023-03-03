#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <locale.h>
#include <cstring>

int main() {
	setlocale(LC_ALL, "Russian");

	int fd = open("./os9.txt", O_CREAT | O_RDWR, 0644); 
	if (fd == -1) {
		perror("Ошибка при создании файла");
		return 1;
	}
	char buf[100];
	char text[] = "_";
	ssize_t text_len = sizeof(text) - 1;
	write(fd, text, text_len);

	long pos = lseek(fd, 0, SEEK_SET);
	printf("Текущий смещение: %ld\n", pos);
	read(fd, buf, sizeof(buf));
	printf("Прочитано из файла: %s\n", buf);
	memset(buf, '\0', sizeof(buf));


	pos = lseek(fd, 40, SEEK_CUR); 
	printf("Текущий смещение: %ld\n", pos);
	read(fd, buf, sizeof(buf)); 
	printf("Прочитано из файла: %s\n", buf);
	memset(buf, '\0', sizeof(buf));

	pos = lseek(fd, -50, SEEK_END);
	printf("Новое смещение: %ld\n", pos);
	read(fd, buf, sizeof(buf));
	printf("Прочитано из файла: %s\n", buf);

	close(fd);
	return 0;
}
