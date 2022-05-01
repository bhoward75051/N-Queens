data <- read.table(file="newtestResults.txt", sep=" ", header=FALSE)
colnames(data) <- c("n","depth","processes","real","user")
data
data12 <- data[ which(data$n == 14), ]
data12_1 <- data12[ which(data$processes == 1 ), ]
data12_2 <- data[ which(data12$processes == 2 ), ]
data12_3 <- data[ which(data$processes == 4 ), ]
data12
plot(data12_1[, 2], data12_1[, 4])

plot(data12_2[,2], data12_2[,6])
lines(data[,3], col = 'red')
lines(data[,4], col = 'green')
lines(data[,6], col = 'blue')

