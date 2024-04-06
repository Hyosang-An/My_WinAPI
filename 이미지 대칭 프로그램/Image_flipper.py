from PIL import Image
import os
import re

# 폴더 경로는 \를 쓰는 경우 맨 앞에 r을 붙이던가, /로 모두 바꾸든가 \\로 써야함.

# 원본 이미지들이 있는 최상위 폴더
source_folder = r"C:\Users\gytha\Documents\Programming\Assort51th\My_WinAPI\build\contents\animation\Boss\Goopy Le Grande\Goopy Le Grande L"
# 결과 이미지들을 저장할 최상위 폴더
target_folder = r"C:/Users/gytha/Documents/Programming/Assort51th/My_WinAPI/build/contents/animation/Boss/Goopy Le Grande/Goopy Le Grande R"

# source_folder의 존재 여부 확인
if not os.path.exists(source_folder):
    print(f"원본 폴더가 존재하지 않습니다: {source_folder}")
    exit()  # 원본 폴더가 없으면 프로그램 종료

# target_folder가 없으면 생성
if not os.path.exists(target_folder):
    os.makedirs(target_folder)
    print(f"결과 폴더를 생성했습니다: {target_folder}")

# 파일 이름 패턴 확인 및 새 파일 이름 생성
def get_new_file_name(file_name):
    pattern = re.compile(r'(.+)_([0-9]{4})\.png$')
    match = pattern.match(file_name)
    if match:
        # 파일 이름이 패턴과 일치하는 경우
        base_name, number = match.groups()
        new_file_name = f"{base_name}_L_{number}.png"
    else:
        # 일치하지 않는 경우, 기존 이름에 _L만 추가
        new_file_name = os.path.splitext(file_name)[0] + '_L.png'
    return new_file_name

# 주어진 경로에 대하여 원본 폴더 구조를 유지하며 결과 폴더 구조를 생성
def ensure_folder_structure(source_path, target_base):
    relative_path = os.path.relpath(source_path, start=source_folder)
    target_path = os.path.join(target_base, relative_path)
    if not os.path.exists(target_path):
        os.makedirs(target_path)
    return target_path

print("작업 중...")

# 모든 하위 폴더를 포함하여 이미지 파일 처리
for root, dirs, files in os.walk(source_folder):
    for file_name in files:
        if file_name.lower().endswith('.png'):
            source_path = os.path.join(root, file_name)
            target_path = ensure_folder_structure(root, target_folder)
            new_file_name = get_new_file_name(file_name)
            new_image_path = os.path.join(target_path, new_file_name)

            with Image.open(source_path) as img:
                flipped_img = img.transpose(Image.FLIP_LEFT_RIGHT)
                flipped_img.save(new_image_path)

print("모든 PNG 이미지가 처리되었습니다.")
