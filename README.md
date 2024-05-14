# The Hayasa programming language

***Hayasa is a programming language which contains only armenian keywords and symbols that exists in armenian keyboard layout***.

---

## Introduction

Hayasa-ն ծրագրավորման լեզու է, որի բաղկացուցիչ մասը կազմող լեքսիկական և քերականական բաղադրիչները միմիայն հայերեն լեզվով են, իսկ ուղղագրությունը կազմող սիմվոլները հայերեն ստեղնաշարին համապատասխան։

## Table of Contents

- [Installation](#installation)
- [Getting Started](#getting-started)
- [Examples](#examples)
- [Contributing](#contributing)

## Installation

**Hayasa** լեզվով կոդ գրելու և աշխատեցնելու համար անհրաժեշտ է նախևառաջ կլոնավորել ռեպոզիտորիան։

```
git clone [repository_path]
```

Քանի    որ այն գրված է C լեզվով անհրաժեշտ է նաև համակարգչում ունենալ C լեզվի թարգմանիչ, օրինակ՝ **clang**, **gcc** և այլն։

## Getting Started

1. Աշխատանքը Hayasa-ով սկսելու համար պետք է կոմպիլյացնել նախագիծը ՝
```
make
```
կամ
```
make install
```

2. Այնուհետև ստացված իրականացվող ֆայլի՝ hayasa֊ի միջոցով աշխատեցնում ենք նպատակային կոդը, փոխանցելով որպես արգումենտ նպատակային կոդը պարունակող ֆայլը։ Օրինակ՝

```
./hayasa program.hy
```

## Examples

Hayasa-ով գրված ծրագրի կոդի օրինակներ՝

փոփոխականներ՝
```
ՀԱՅ անուն ՎԵՐԱԳՐԻՐ "Պողոս";
ՀԱՅ ազգանուն ՎԵՐԱԳՐԻՐ "Պետրոսյան";
ՀԱՅ տարիք ՎԵՐԱԳՐԻՐ 33;
ՀԱՅ գործազրկություն ՎԵՐԱԳՐԻՐ ՃՇՄԱՐԻՏ;

ՏՊԻՐՏՈՂ « "Անուն։ " և անուն »;
ՏՊԻՐՏՈՂ « "Ազգանուն։ " և ազգանուն »;
ՏՊԻՐՏՈՂ « "Տարիք։ " և տարիք »;
ՏՊԻՐՏՈՂ « "Գործազրկություն։ " և գործազրկություն »;
```
գործառույթ (function) ՝
```
ԳՈՐԾԱՌՈՒՅԹ ՏպիրԱրգումենտները « ա և բ »
ՍԿԻԶԲ
	ՏՊԻՐՏՈՂ « ա և " " և բ »;
ԱՎԱՐՏ;

ՀԱՅ անուն ՎԵՐԱԳՐԻՐ "Մովսես";
ՀԱՅ տարիք ՎԵՐԱԳՐԻՐ 34;

ՏպիրԱրգումենտները « անուն և տարիք »;
ՏպիրԱրգումենտները « "Բարև" և ՃՇՄԱՐԻՏ »;
ՏպիրԱրգումենտները « "Բարև" և 3 »;
ՏպիրԱրգումենտները « "Բարև" և "չորս" »;
```
պայմանի կառուցվածք ՝
```
ՀԱՅ թիվ ՎԵՐԱԳՐԻՐ 11;

ԵԹԵ « ՀԱՎԱՍԱՐ « ՄՆԱՑՈՐԴ « թիվ և 2 » և 0 » » ԱՊԱ
	ՏՊԻՐՏՈՂ « թիվ և "֊ը զույգ է" »
ԱՅԼԱՊԵՍ
	ՏՊԻՐՏՈՂ « թիվ և "֊ը կենտ է" »;
ԱՎԱՐՏ;
```
մեկնաբանություններ՝ միատող և բազմատող ՝
```
― Միատող մեկնաբանություններ

ՏՊԻՐՏՈՂ « "Բարև" և " " և "աշխարհ" »;

/
	Բազմատող
	մեկնաբանություններ
/
```

## Contributing

Contributions are welcome! To contribute to this repository, follow these steps:

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -am 'Add some fooBar'`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Create a new Pull Request

For major changes, please open an issue first to discuss what you would like to change.

## License

This project is licensed under the [License Name] - see the [LICENSE.md](LICENSE.md) file for details.
