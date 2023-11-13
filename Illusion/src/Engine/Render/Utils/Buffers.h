/*
 * ======================== Buffers.h ==========================
 *                          -- ils --
 *                                         CREATE -- 2023.01.14
 *                                         MODIFY --
 * ------------------------------------------------------------
 * The buffer classes
 * VBO, IBO, FBO, and RBO
 * ----------------------------
 */

#pragma once

 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{
	// Type of the vertex data
	enum class VertexDataType
	{
		None= 0,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};

	// Get the size of each vertex data
	static uint32_t VertexDataTypeSize(VertexDataType type)
	{
		switch (type)
		{
		case VertexDataType::Float:			return 4;
		case VertexDataType::Float2:		return 4 * 2;
		case VertexDataType::Float3:		return 4 * 3;
		case VertexDataType::Float4:		return 4 * 4;
		case VertexDataType::Mat3:			return 4 * 3 * 3;
		case VertexDataType::Mat4:			return 4 * 4 * 4;
		case VertexDataType::Int:			return 4;
		case VertexDataType::Int2:			return 4 * 2;
		case VertexDataType::Int3:			return 4 * 3;
		case VertexDataType::Int4:			return 4 * 4;
		case VertexDataType::Bool:			return 1;
		}

		ILLUSION_CORE_ASSERT(false, "Unknown Shader Data Type!");
		return 0;
	}

	// Vertex Data
	struct VertexData
	{
		std::string Name;
		VertexDataType Type;
		size_t Offset;
		uint32_t Size;
		bool Normalized;

		VertexData() = default;

		VertexData(VertexDataType type, const std::string& name, bool normalized = false)
			:Name(name), Type(type), Size(VertexDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		// Get the number number of components of each vertex data
		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
				case VertexDataType::Float:			return 1;
				case VertexDataType::Float2:		return 2;
				case VertexDataType::Float3:		return 3;
				case VertexDataType::Float4:		return 4;
				case VertexDataType::Mat3:			return 3; // 3 * float3
				case VertexDataType::Mat4:			return 4; // 4 * float4
				case VertexDataType::Int:			return 1;
				case VertexDataType::Int2:			return 2;
				case VertexDataType::Int3:			return 3;
				case VertexDataType::Int4:			return 4;
				case VertexDataType::Bool:			return 1;

			}

			ILLUSION_CORE_ASSERT(false, "Unknown Shader Data Type!");
			return 0;
		}
	};

	// The layout of vertex buffer data
	class VBODataLayout
	{
	public:

		VBODataLayout() = default;

		VBODataLayout(const std::initializer_list<VertexData>& vbodata)
			: m_VBOData(vbodata)
		{
			CalculateOffsetAndStride();
		}

		uint32_t GetStride() const { return m_Stride; }
		std::vector<VertexData> GetVertexData() const { return m_VBOData; }

		// Discard temporarily
		//std::vector<VertexData>::iterator begin() { return m_VBOData.begin(); }
		//std::vector<VertexData>::iterator end() { return m_VBOData.end(); }
		std::vector<VertexData>::const_iterator begin() const { return m_VBOData.begin(); }
		std::vector<VertexData>::const_iterator end() const { return m_VBOData.end(); }

	private:
		// Get the offset and stride for each vertex data
		void CalculateOffsetAndStride()
		{
			size_t offset = 0;
			m_Stride = 0;
			for (auto& vertexdata : m_VBOData)
			{
				vertexdata.Offset = offset;
				offset += vertexdata.Size;
				m_Stride += vertexdata.Size;
			}
		}

	private:
		std::vector<VertexData> m_VBOData;
		uint32_t m_Stride = 0;
	};


	//--------------------Vertex Buffer--------------------
	//------------------------ VBO ------------------------
	class VBO
	{
	public:
		VBO(float* vertices, uint32_t size);
		VBO(uint32_t size);

		~VBO();

		void Bind() const;

		void Unbind() const;

		void SetDataLayout(const VBODataLayout& layout) { m_Layout = layout; }

		void SendData(const void* data, uint32_t size = 0);

		const VBODataLayout& GetDataLayout() const { return m_Layout; }


	private:
		VBODataLayout m_Layout;

		uint32_t m_VBO;
	};

	//--------------------Index Buffer---------------------
	//------------------------ IBO ------------------------
	class IBO
	{
	public:
		IBO(uint32_t* indices, uint32_t count);

		~IBO();

		void Bind() const;

		uint32_t GetCount() { return m_Count; }

		void Unbind() const;

	private:
		uint32_t m_IBO;

		uint32_t m_Count;

	};

	//--------------------Frame Buffer---------------------
	//------------------------ FBO ------------------------
	class FBO
	{
	public:
		FBO(uint32_t width, uint32_t height);

		~FBO();

		void Bind() const;

		void Unbind() const;

		uint32_t GetColorAttachment() const { return m_ColorAttachment; }

		void Resize(uint32_t width, uint32_t height);

	private:
		uint32_t m_FBO;

		uint32_t m_ColorAttachment;
		uint32_t m_DepthAttachment;

		uint32_t m_Width, m_Height;

	};

	//--------------------namespace: Illusion ends--------------------
}
