-- @block
SHOW DATABASES;
-- @block
SELECT *
FROM company;
-- @block
SELECT *
FROM company
WHERE ticker = "AAPL";
-- @block
SELECT *
FROM stockdata;
-- @block
SELECT *
FROM stockdata
WHERE ticker = "AAPL";
-- @block
CREATE INDEX ticker_index ON stockdata (ticker);
-- @block
CREATE TABLE stockdata (
    id INT NOT NULL AUTO_INCREMENT,
    ticker varchar(10) NOT NULL,
    date datetime NOT NULL,
    open float NOT NULL,
    close float NOT NULL,
    high float NOT NULL,
    low float NOT NULL,
    volume int NOT NULL,
    dividends float(4, 3) NOT NULL,
    stocksplit int NOT NULL,
    PRIMARY KEY (id),
    FOREIGN KEY (ticker) REFERENCES company (ticker)
);
-- @block
SELECT *
FROM company
    INNER JOIN stockdata ON company.ticker = stockdata.ticker;
-- @block
SELECT *
FROM company
    LEFT JOIN stockdata ON company.ticker = stockdata.ticker;