관련 TIL : https://hnjog.github.io/c++/Week2Task2/

## 클래스 설명
이전에 구현해둔 Task1의 기반을 가져다 사용<br>

```
클래스 구조

Character
- 체력 등의 스탯과 스킬을 관리하는 캐릭터 주체
- Stat을 Base와 Enhanced로 나누어 기본 스탯과 강화 영향을 받은 스탯으로 분류
- Attack, Hit 함수를 순수 가상함수(=0)으로 구현하여 실체화를 방지

Skill
- 대미지 비율과 마나 소모율을 관리하는 클래스
  (구조체로 구현했어도 괜찮았을듯)

Player
- Character를 상속받고 Inventory를 관리하는 Player 주체
- 전직용 Enum을 넣어두었고, Player 자신은 Nobiss(초보자)로 선언
 (실체화 자체는 가능)
- Level 변수 추가(Monster에는 필요 없으므로)

Inventory
- 포션과 같은 아이템을 추가, 사용하도록 관리하는 주체
  (다만 이번에는 사용을 하지 않는다)

Warrior, Magician, Thief, Archor
- 각각 Player를 상속받으며, 내부에서 Attack을 재정의한 자식 클래스들
- 다형성을 기반으로 MainGame에선 업캐스팅으로 Attack 호출해주면 된다

```

추가 파일들<br>

```
Utils - IsNotValid, SafeDelete 등의 매크로를 별도로 저장한 헤더 파일
Enums - Enum을 모아 놓은 헤더 파일
```

## 트러블 슈팅
~~솔직히 오늘은 없을 줄 알았다~~<br>

<img width="809" height="736" alt="Image" src="https://github.com/user-attachments/assets/7d161988-c361-4ed6-ac1c-7784c59252dc" /><br>

MainGame에서 직업별 클래스를 생성하는 중<br>
이상하게도 Warrior 클래스가 인식이 되지 않는 문제가 있었다<br>

<img width="476" height="55" alt="Image" src="https://github.com/user-attachments/assets/457522dc-0764-429a-9513-d1641c7295cd" /><br>

error는 C2061로서, 구문 오류이다<br>

<img width="293" height="150" alt="Image" src="https://github.com/user-attachments/assets/3963d500-d122-411b-9cb7-13e3e64b1526" /><br>

그런데 분명 include를 해놓았기에<br>
매우 이상한 상황이였다<br>

그렇기에 VS를 껏다 켰는데도<br>
문제가 지속되자<br>
왜 이러지 싶어서 이상하리만큼 색이 다른 Warrior에 키워드를 올린 순간...<br>

<img width="392" height="163" alt="Image" src="https://github.com/user-attachments/assets/662f2edf-53f6-494e-88f2-c10391cea5bf" /><br>

응...???<br>
Enum...????<br><br>

<img width="232" height="294" alt="Image" src="https://github.com/user-attachments/assets/30b85ef0-e255-4c40-af4a-f77d591cab6a" /><br>

~~Enum.h 또 너야?~~<br>
~~(사실 이렇게 작성한 내 잘못이다)~~<br>

전직 개념을 사용할때<br>
클래스에 대한 Enum을 통하여 실제로 Dynamic_cast를<br>
호출할만한 거리를 줄이는 것은 성능상 도움이 되기에<br>
나는 Player용 변수로 classIdx라는 Enum을 선언했었다<br>

근데 문제는 ~~멍청하게도~~ 해당 Enum과<br>
클래스 이름을 완벽하게 같이 설정해버렸다는 것...<br>

<img width="237" height="283" alt="Image" src="https://github.com/user-attachments/assets/60eb48ea-58db-446b-80a0-303e8aeee0c7" /><br>

Enum 이름을 유니크하게 설정하는 것으로 바꿔주었다<br>
문제 없이 동작한다!<br>
