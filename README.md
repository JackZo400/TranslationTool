# 专业文档翻译工具

一个基于C++和Qt开发的跨平台文档翻译工具，支持多种文件格式和专业术语翻译。

## 功能特性

### 🎯 核心功能
- **多格式支持**: 支持TXT、DOCX、PDF、HTML、XML、JSON等文件格式
- **专业术语翻译**: 内置医学、法律、技术等多个领域的专业术语词典
- **批量翻译**: 支持大文件分块翻译，显示实时进度
- **格式保持**: 翻译后保持原始文档格式

### 🚀 技术特点
- **高性能**: 优化的文本处理和翻译算法
- **跨平台**: 兼容Windows、Linux、macOS
- **现代化UI**: 基于Qt6的现代化用户界面
- **可扩展**: 模块化设计，易于扩展新功能

## 系统要求

### 最低配置
- **操作系统**: Windows 10/11, Ubuntu 18.04+, macOS 10.14+
- **编译器**: Visual Studio 2022, GCC 9+, Clang 10+
- **Qt版本**: Qt 6.5.3 或更高版本
- **内存**: 4GB RAM
- **存储**: 500MB 可用空间

### 推荐配置
- **操作系统**: Windows 11, Ubuntu 20.04+, macOS 12+
- **编译器**: Visual Studio 2022, GCC 11+, Clang 13+
- **Qt版本**: Qt 6.5.3
- **内存**: 8GB RAM 或更多
- **存储**: 1GB 可用空间

## 安装指南

### 前置依赖

1. **安装Qt6**
   ```bash
   # 使用Qt在线安装器
   # 下载地址: https://www.qt.io/download-open-source
   # 选择 Qt 6.5.3 和以下组件:
   # - Qt Core
   # - Qt Widgets
   # - Qt Network
   # - CMake
   ```

2. **安装编译工具**
   - **Windows**: Visual Studio 2022 with C++ workload
   - **Ubuntu**: `sudo apt install build-essential cmake`
   - **macOS**: Xcode Command Line Tools

### 编译步骤

1. **克隆项目**
   ```bash
   git clone https://github.com/JackZoo400/translation-tool.git
   cd translation-tool
   ```

2. **创建构建目录**
   ```bash
   mkdir build
   cd build
   ```

3. **配置项目**
   ```bash
   # Windows (Visual Studio 2022)
   cmake -G "Visual Studio 17 2022" -A x64 ..
   
   # Linux
   cmake ..
   
   # macOS
   cmake -G "Xcode" ..
   ```

4. **编译项目**
   ```bash
   # Windows
   cmake --build . --config Release
   
   # Linux/macOS
   cmake --build . --config Release -j4
   ```

5. **运行应用**
   ```bash
   # Windows
   ./Release/TranslationTool.exe
   
   # Linux
   ./TranslationTool
   
   # macOS
   open TranslationTool.app
   ```

## 使用说明

### 基本操作

1. **打开文件**
   - 点击"打开文件"按钮或使用快捷键 `Ctrl+O`
   - 选择要翻译的文档文件
   - 支持的文件格式: TXT, DOCX, PDF, HTML, XML, JSON

2. **设置翻译参数**
   - **源语言**: 选择原文语言（支持自动检测）
   - **目标语言**: 选择翻译目标语言
   - **专业领域**: 根据文档内容选择对应领域
   - **API密钥**: 输入翻译服务API密钥

3. **开始翻译**
   - 点击"开始翻译"按钮或使用快捷键 `Ctrl+T`
   - 查看实时翻译进度
   - 翻译完成后在右侧窗口查看结果

4. **保存翻译结果**
   - 点击"保存翻译"按钮或使用快捷键 `Ctrl+S`
   - 选择保存格式和位置

### 高级功能

#### 专业术语管理
工具内置多个专业领域的术语词典：
- **医学**: 医学术语准确翻译
- **法律**: 法律术语标准化
- **技术**: 技术术语统一
- **学术**: 学术用语规范化
- **商务**: 商务术语专业化

#### 批量处理
- 自动分割大文件
- 并行翻译处理
- 进度实时显示
- 错误恢复机制

## 配置说明

### 翻译服务配置

目前支持以下翻译服务：
- Microsoft Translator API
- Google Cloud Translation API
- 自定义翻译服务

在设置界面配置API密钥和端点：

```json
{
  "service": "microsoft",
  "api_key": "your-api-key",
  "endpoint": "https://api.cognitive.microsofttranslator.com",
  "region": "global"
}
```

### 自定义术语

在 `config/terminology.json` 中添加自定义术语：

```json
{
  "medical": {
    "CT scan": "CT扫描",
    "MRI": "磁共振成像"
  },
  "technical": {
    "API": "应用程序接口",
    "SDK": "软件开发工具包"
  }
}
```

## 项目结构

```
TranslationTool/
├── src/                    # 源代码目录
│   ├── main.cpp           # 程序入口
│   ├── MainWindow.h/cpp   # 主窗口类
│   ├── TranslationEngine.h/cpp  # 翻译引擎
│   ├── FileHandler.h/cpp  # 文件处理器
│   └── Settings.h/cpp     # 设置管理
├── resources/             # 资源文件
│   ├── icons/            # 图标资源
│   └── terminology/      # 术语词典
├── config/               # 配置文件
├── docs/                 # 文档
├── tests/                # 测试代码
└── CMakeLists.txt        # 构建配置
```

## 故障排除

### 常见问题

1. **编译错误: 找不到Qt模块**
   ```
   解决方案: 确保安装了正确的Qt版本和组件
   ```

2. **运行时错误: 无法加载翻译服务**
   ```
   解决方案: 检查API密钥配置和网络连接
   ```

3. **文件格式不支持**
   ```
   解决方案: 确保安装了对应的文档处理库
   ```

### 调试模式

启用调试输出：
```bash
# 设置环境变量
export QT_LOGGING_RULES="*.debug=true"
./TranslationTool
```

## 开发指南

### 代码规范
- 使用C++17标准
- 遵循Qt编码规范
- 使用CMake构建系统
- 编写单元测试

### 添加新功能

1. **添加新的文件格式支持**
   - 在 `FileHandler` 类中添加新的格式处理
   - 更新文件格式检测逻辑

2. **添加新的翻译服务**
   - 继承 `TranslationEngine` 基类
   - 实现特定的API调用逻辑

3. **添加新的专业领域**
   - 在 `terminology/` 目录添加术语文件
   - 更新领域选择逻辑

## 贡献指南

我们欢迎社区贡献！请遵循以下步骤：

1. Fork 项目
2. 创建功能分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 开启 Pull Request

### 开发环境设置

1. 安装开发工具
2. 配置代码格式化工具
3. 设置调试环境
4. 运行测试套件

## 许可证

本项目采用 MIT 许可证 - 查看 [LICENSE](LICENSE) 文件了解详情。

## 更新日志

### v1.0.0 (2025-11-09)
- 初始版本发布
- 支持基本文档翻译功能
- 内置专业术语词典
- 多格式文件支持

## 技术支持

如果您遇到问题，可以通过以下方式获取帮助：

- 📧 邮箱: JackWhite114514@Outlook.com
- 💬 讨论区: [GitHub Discussions](https://github.com/JackZoo400/translation-tool/discussions)
- 🐛 问题报告: [GitHub Issues](https://github.com/JackZoo400/translation-tool/issues)

## 致谢

感谢以下开源项目的支持：
- [Qt](https://www.qt.io/) - 跨平台应用框架
- [CMake](https://cmake.org/) - 构建系统
- 以及其他所有依赖库的贡献者

---

**注意**: 本项目仍在积极开发中，功能可能会发生变化。建议定期检查更新以获取最新功能和改进。
