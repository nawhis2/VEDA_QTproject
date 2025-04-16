# VEDA_QTproject - 강한 연락처

VEDA 강시환 X 한영서의 연락처 프로젝트입니다.

Qt 6.8.3 기반 연락처 관리 애플리케이션으로, 연락처의 그룹/서브그룹 구조와 세부 정보를 트리 뷰로 시각화하고, JSON 파일로 데이터를 저장 및 불러올 수 있습니다. 
날씨 정보, SNS 프로필 연결 등 API 연동 기능도 일부 포함되어 있습니다.

## 주요 기능

- 연락처 트리뷰(QTreeView) 기반 관리
- 즐겨찾기 설정 기능
- 연락처 검색 대화상자(SearchDialog)
- 연락처 상세정보 패널(QStackedLayout)
- JSON을 통한 데이터 저장 및 불러오기
- 날씨 정보 표시 (외부리소스로 날씨 API를 활용 -> `WeatherManager`)
- SNS 링크 연결 (아이콘 및 URL)
- 생일 알림 기능

## 빌드 방법

### 요구사항
- Qt 6.8.3
- CMake >= 3.15
- Windows 11

QT Creator를 활용하여 빌드하는 것을 추천합니다.

## 프로젝트 구조

```
makefile
복사
편집
VEDA_QTproject/
├── include/           # 헤더 파일
├── src/               # 구현 파일
├── ui/                # Qt Designer UI 파일
├── resources/         # 이미지 및 폰트 리소스
├── test_file/         # 테스트 JSON 데이터
├── CMakeLists.txt     # 빌드 스크립트
├── resources.qrc      # Qt 리소스 정의
└── README.md
```

## 프로젝트 상세 기능 소개

### 메인 화면

![alt text](./images/main.png)

- 트리 뷰(TreeView)를 통해 연락처를 그룹/서브그룹 구조로 한눈에 확인
- 메인 화면 연락처는 그룹과 이름만 확인 가능
- 상단 메뉴에서는 데이터 추가/제거/검색/저장하기/불러오기를 사용 가능
- 날씨 API 연동을 통해 현재 날씨 정보를 상단에서 실시간으로 표시
- 오늘의 날짜와 일치하는 생일자를 하단에 표시


### 데이터 추가

![alt text](./images/detail.png)

- 툴바에서 '추가' 버튼을 클릭하면 세부 페이지의 입력창이 나타남
- 연락처의 모든 정보를 입력 가능(이름, 번호, E-mail, 주소, 생일, SNS, 메모)
- SNS에 적인 정보를 통해 '연결' 버튼을 클릭하면 URL 자동으로 연결
- 새로 추가된 연락처는 현재 선택된 그룹에 자동으로 배치


### 데이터 제거
![alt text](./images/delete1.png)

![alt text](./images/delete2.png)

- 메인 화면의 트리 뷰(TreeView)에서 원하는 연락처를 선택한 뒤, '삭제' 버튼을 클릭하면 해당 연락처가 삭제
- 선택을 하지 않고 버튼을 클릭시 확인 메세지 박스를 표시


### 데이터 검색

![alt text](./images/searchdialog.png)

![alt text](./images/searchresult.png)

![alt text](./images/searchdetail.png)

- 메인 화면에서 '검색' 버튼을 클릭하면 별도의 검색창이 나타남
- 검색창에 키워드를 입력하면 일치하는 연락처 리스트가 하단 테이블에 표시
- 단어 하나 입력해도 그 단어에 일치하는 모든 연락처 표시
- 하단 테이블에서 해당 연락처를 더블 클릭하면 해당 연락처의 세부 페이지로 전환
- 검색 결과는 동일 인물이 있을 경우, 구분할 수 있게 이름과 전화번호를 표시


### 데이터 수정

![alt text](./images/fixdata.png)

![alt text](./images/fixcomplete.png)

- 선택한 연락처의 세부 페이지에서 수정을 하고 '저장' 버튼을 클릭하면 변경 사항이 적용
- 메인 화면과 해당 연락처 세부 페이지가 변경된 것을 확인 가능


### 데이터 불러오기

![alt text](./images/fileLoad.png)

![alt text](./images/loadcomplete.png)

- JSON 파일로 저장된 연락처 데이터를 불러오기 가능
- 메뉴의 '불러오기' 버튼을 클릭한 후 JSON 파일을 선택하면 기존 데이터에 덮어쓰지 않고 불러온 파일 데이터로 갱신


### 데이터 저장하기

![alt text](./images/savefile.png)

![alt text](./images/savecomplete.png)

- 현재 메인 연락처에 등록된 모든 연락처 데이터를 JSON 형식으로 저장
- 저장 시에는 사용자에게 파일 경로를 묻고, 해당 경로에 JSON 파일이 생성


### 생일 알림

![alt text](./images/birth.png)

- 오늘의 날짜와 일치하는 생일자가 있을 시, 하단에 생일자 이름 표시
- 오늘의 날짜와 일치하는 생일자가 없을 시, 하단에 생일자가 없다고 표시
- 생일자 연락처 제거 시, 생일 알림도 같이 업데이트


## 문제점

1.

2.

3.


## 소감

