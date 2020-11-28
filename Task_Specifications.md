# DSA 2020 HW2.4 Specifications

In this spec, first we will tell you how the TAs are going to test your program.
Next, the formats of the input and output will be given with full instructions and some examples.
In the end, some hints and FAQs are listed.

### Testing
You should provide your own Makefile.
The TAs will run `make` to compile your source code and use the following command to test your program:
```
./demo /path/to/data/file
```
For example, the TAs may run the following on the R217 workstation:
```
./demo /tmp2/dsahw2/CriteoSearchData
```

Note that the designated file path will be set by the TAs. Your program should open the designated file and read it.


### Input Size & Memory and Time Constraint
Memory: Workstation Memory Size
Time constraint: 1 hour

**first part (100,000 lines of data)**
1 <= # queries <= 100

**second part (1,000,000 lines of data)**
1 <= # queries <= 1000

**thrid part (all lines of data)**
1 <= # queries <= 10000

Disclaimer: **valid** means **exist** here

**get u p t**
- u is a **valid** user id
- p is a **valid** product id
- t is a **valid** timestamp
- we promise that the `u p t` exists *exactly once* in the data

**purchased u**
- u is a **valid** user id
- if the result contains product_id == '-1', you should still output it.

**clicked p1 p2**
- p1 p2 are valid product ids (p1, p2 != -1)

**profit t $\theta$**
- t is an integer, $0 \le t \le 2^{31} -1$
- $\theta$ is a float, $0 \le t \le 1$ 


### Format
Your demo program should work like a simple command line. That is, after executing the demo file, it can let the user enter some commands. Each command takes one line.
And your program should read the command on stdin and give the response on stdout. Also, you have to separate your responses with one line of 20 “*”. For example,
```
********************
# your output
# ...
# your output in the same response
********************
```
In this task, the TAs will use 5 commands:
- get(u, p, t)
- purchased(u)
- clicked(p1, p2)
- profit(t, θ)
- quit

Note that `quit` has no parameter, and can be used to leave the running demo program.
The formats for each command are listed below, and we will give a set of sample input/output including all commands.

1. get

- input
```
get u p t
```
- output
```
********************
sale
********************
```


2. purchased

- input
```
purchased u
```
- output
```
********************
product_id click_timestamp price age_group gender
.
.
.
product_id click_timestamp price age_group gender
********************
```

**Please sort first by product_id then by click_timestamp, both in increasing order.**

3. clicked

- input
```
clicked p1 p2
```
- output
```
********************
user_id
.
.
.
user_id
********************
```

**Please sort by user_id in increasing order.**

4. profit

- input
```
profit t θ
```
- output
```
********************
user_id
.
.
.
user_id
********************
```

**Please output the first 10 user_id sorted in increasing order. (timestamp is inclusive, i.e. consider all timestamps >= t)**

### Sample input/output

*Note that we have added one more `purchased` query*.


- input
```
get FFFF5CC6BC5E0E4580271AD4C0ABA182 A8DA41EE400550D0886E7B1A7F30522E 1596580478
get FFFF5CC6BC5E0E4580271AD4C0ABA182 CBC52ED142276B4BE1870C321670D059 1600393392
purchased F2848A2DC18D8DDFB75B826E21A18257
purchased BA538A2B4B87250A2D863A7494FD27B2
clicked 3A1E897AD1858494048EB6D4C29DAE26 69F6F839E345E5394FB2A4C0B08465B1
clicked CDF965FB198F556D2451724F84F5ABB3 69F6F839E345E5394FB2A4C0B08465B1
clicked 3A1E897AD1858494048EB6D4C29DAE26 CDF965FB198F556D2451724F84F5ABB3
profit 1604301854 0.9
quit
```
- output
```
********************
1
********************
********************
0
********************
********************
69F6F839E345E5394FB2A4C0B08465B1 1600146468 14.99 88460293E9517D21E39AA889BD5AADC8 A5D15FC386510762EC0DDFF54ABE6F94
********************
********************
-1 1599010085 21.9 -1 -1
4AA3073948A684BDA548ACE06FCC3BFC 1602779367 45.0 -1 -1
FB33B4755EFF79FFFA6EB8BC7FE94BF7 1600648935 59.0 -1 -1
********************
********************
F2848A2DC18D8DDFB75B826E21A18257
********************
********************
F2848A2DC18D8DDFB75B826E21A18257
********************
********************
F2848A2DC18D8DDFB75B826E21A18257
********************
********************
35DF2152F482FA238708636E20BFF889
7163521E190458CE5C1E0663598D94C7
91C6D324153A4E53836CBEB1F8FAEA27
********************
```

### Hints about data

- Each line of the data contains 23 fields/columns in the following format (`\t` denotes tab): `<Sale>\t<SalesAmountInEuro>\t<time_delay_for_conversion>\t<click_timestamp>\t<nb_clicks_1week>\t<product_price>\t<product_age_group>\t<device_type>\t<audience_id>\t<product_gender>\t<product_brand>\t<product_category(1-7)>\t<product_country>\t<product_id>\t<product_title>\t<partner_id>\t<user_id>`
- `<product_category(1-7)>` is in fact composed of 7 fields, also separated by tabs
- `<product_title>` may contain spaces, and may be an empty string
- More details can be found at https://ailab.criteo.com/criteo-sponsored-search-conversion-log-dataset/


### FAQ

- For the `purchased` function, should I output the entries where `product_id` is -1?
    - Yes, please include such entries. Note that -1 should be in the beginning by lexicographical order

