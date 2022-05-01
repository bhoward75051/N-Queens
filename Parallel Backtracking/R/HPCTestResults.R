data <- read.table(file="testResultsHPC.txt", sep=" ", header=FALSE)
colnames(data) <- c("pass","n","depth","processes","real","user","sys")
data
typeof(data$real)
data12 <- data[ which(data$n == 12 & data$pass == 0), ]
data12_1 <- data[ which(data$processes == 1 ), ]
data12_2 <- data[ which(data12$processes == 2 ), ]
data12_3 <- data[ which(data$processes == 4 ), ]

plot(data[, 3], data[, 6])

plot(data12_2[,2], data12_2[,6])
lines(data[,3], col = 'red')
lines(data[,4], col = 'green')
lines(data[,6], col = 'blue')

