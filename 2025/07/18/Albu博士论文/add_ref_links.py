import re

def process_references(content):
    content = re.sub(r'<span id="ref-\d+"></span>', '', content)
    
    content = re.sub(r'^(\d+)\. ', r'<span id="ref-\1"></span>\1. ', content, flags=re.MULTILINE)
    
    def replace_multi_ref(match):
        nums = match.group(1)
        links = []
        for num in re.findall(r'\d+', nums):
            links.append(f'[[{num}]](#ref-{num})')
        return ', '.join(links)
    
    content = re.sub(r'\[(\d+(?:,\s*\d+)+)\]', replace_multi_ref, content)
    content = re.sub(r'\[(\d+)\]', r'[[\1]](#ref-\1)', content)
    
    return content

input_file = r'd:\hexoblog\source\_posts\Albu博士论文.md'
output_file = r'd:\hexoblog\source\_posts\Albu博士论文\Albu博士论文_with_ref_links.md'

with open(input_file, 'r', encoding='utf-8') as f:
    content = f.read()

content = process_references(content)

with open(output_file, 'w', encoding='utf-8') as f:
    f.write(content)

print(f"处理完成！已生成文件: {output_file}")