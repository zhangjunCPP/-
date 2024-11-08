import os
import shutil
import subprocess
import time

def run_tests(base_path, problem_name, num_tests, in_suffix, out_suffix):
	# 获取题目文件夹路径
	problem_path = os.path.join(base_path, problem_name)

	# 编译选手程序
	source_code = os.path.join(problem_path, f"{problem_name}.cpp")

	# 判断操作系统，设置可执行文件名
	if os.name == 'nt':  # Windows
		executable = os.path.join(problem_path, f"{problem_name}.exe")
	else:  # Linux/Unix/MacOS
		executable = os.path.join(problem_path, problem_name)

	print(f"编译 {source_code} ...")
	compile_result = subprocess.run(["g++", source_code,"-std=c++14","-O2","-lm","-o", executable], capture_output=True)
	if compile_result.returncode != 0:
		print(f"编译 {problem_name} 失败！")
		print(compile_result.stderr.decode())  # 输出编译错误信息
		return False

	# 初始化要清理的文件列表
	temp_files = []

	try:
		# 遍历所有测试样例
		for i in range(1, num_tests + 1):
			print(f"测试 {problem_name} 的第 {i} 组样例 ...")

			# 构造样例文件名，使用自定义后缀
			in_file = os.path.join(problem_path, f"ex_{problem_name}{i}{in_suffix}")
			out_file = os.path.join(problem_path, f"ex_{problem_name}{i}{out_suffix}")

			# 临时输入输出文件名
			temp_in_file = os.path.join(problem_path, f"{problem_name}.in")
			temp_out_file = os.path.join(problem_path, f"{problem_name}.out")

			# print(f"复制输入文件 {in_file} 到 {temp_in_file}")
			shutil.copyfile(in_file, temp_in_file)
			temp_files.append(temp_in_file)  # 添加到清理列表

			# 运行选手程序，记录执行时间
			# print(f"运行 {executable} ...")
			start_time = time.time()  # 开始计时
			run_result = subprocess.run([executable], cwd=problem_path, capture_output=True)
			end_time = time.time()  # 结束计时

			# 输出运行时间
			duration = end_time - start_time
			print(f"第 {i} 组样例运行时间: {duration:.4f} 秒")

			if run_result.returncode != 0:
				print(f"{problem_name} 程序运行失败：{run_result.stderr.decode()}")
				return False

			# 检查程序是否成功生成输出文件
			if not os.path.exists(temp_out_file):
				print(f"{problem_name} 的第 {i} 组样例未能生成输出文件 {temp_out_file}。")
				return False
			temp_files.append(temp_out_file)  # 添加到清理列表

			# 比较输出文件是否和正确答案一致（忽略行末空格和回车符）
			with open(temp_out_file, 'r') as f_out, open(out_file, 'r') as f_correct:
				output_lines = [line.strip() for line in f_out.readlines()]
				correct_lines = [line.strip() for line in f_correct.readlines()]

				if output_lines != correct_lines:
					print(f"{problem_name} 的第 {i} 组样例未通过。")
					print(f"预期输出: {correct_lines}")
					print(f"实际输出: {output_lines}")
					return False

			print(f"第 {i} 组样例通过！")

	finally:
		# 无论是否成功，始终清理生成的文件
		for file in temp_files:
			if os.path.exists(file):
				os.remove(file)
				# print(f"已删除临时文件 {file}")

		# 删除可执行文件
		if os.path.exists(executable):
			os.remove(executable)
			# print(f"已删除编译出的可执行文件 {executable}")

	# 所有测试样例通过
	# print(f"{problem_name} 通过所有测试样例！")
	return True

def main():
	# 获取当前脚本所在路径
	base_path = os.getcwd()  # 当前工作目录
	problems = {
		"perm": 1000, # 题目名称和样例数
	}

	# 你可以自定义输入和输出文件的后缀名
	in_suffix = ".in"   # 输入文件后缀，例如 ".txt"
	out_suffix = ".ans"  # 输出文件后缀，例如 ".res"

	for problem_name, num_tests in problems.items():
		print(f"测试题目 {problem_name} ...")
		if run_tests(base_path, problem_name, num_tests, in_suffix, out_suffix):
			print(f"{problem_name} 所有测试通过！\n\n\n")
		else:
			print(f"{problem_name} 未通过所有样例。\n\n\n")

if __name__ == "__main__":
	main()